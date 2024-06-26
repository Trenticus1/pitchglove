// Trent's pitch glove code
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

Adafruit_MPU6050 mpu;
RH_ASK driver(2000, 4, 5);
int debug = 1;

String last_note = "n00";
String last_play = "s";

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("PitchGlove Gen2!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  if (!driver.init())
    Serial.println("Wireless init failed");

  Serial.println("");
  delay(100);
}


void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // Read accelerations
  float ax = a.acceleration.y;
  float ay = a.acceleration.x;
  float az = a.acceleration.z;
  
  //Calculation experiments
  //float accel_ang_x = -atan2(ax,az)/2/3.141592654*360; 
  //float accel_ang_y = -atan2(ay,az)/2/3.141592654*360;
  //float accel_ang_x = atan2(ax,az)*180/3.141592654;
  //float pitch = atan2(-ax, sqrt(ay*ay + az*az))*180/3.141592654;
  //float roll = atan2(-ay,az)*180/3.141592654;
  //float roll = atan2(-ay, sqrt(ax*ax + az*az))*180/3.141592654;
  float roll = atan2(ay,sqrt(ax*ax + az*az))*180/3.141592654;
  float pitch = atan2(-ax,sqrt(ay*ay + az*az))*180/3.141592654;
  

  String note = last_note;

  if (fabs(g.gyro.y) < 0.2) {
    if (roll > 82) note = "n01";
      else if (roll > 62 and roll < 78) note = "n02";
      else if (roll > 42 and roll < 58) note = "n03";
      else if (roll > 22 and roll < 38) note = "n04";
      else if (roll > 2 and roll < 18) note = "n05";
      else if (roll > -18 and roll < -2) note = "n06";
      else if (roll > -38 and roll < -22) note = "n07";
      else if (roll > -58 and roll < -42) note = "n08";
      else if (roll > -78 and roll < -62) note = "n09";
      else if (roll <= -82) note = "n10";
  }
  // else note = last_note;
  
  String play = "s";
  
  if (pitch >= 0) play = "p";
    else play = "s";

  // Show results
  if (debug) {
    Serial.print(F("X Pitch: "));
    Serial.print(pitch);
    Serial.print(F("\tY Roll: "));
    Serial.print(roll);
    Serial.print(F("\tNote: "));
    Serial.print(note);
    Serial.print(F("\tPlay: "));
    Serial.print(play);
    Serial.print(F("\tGyro: "));
    Serial.println(g.gyro.y);
  }

  if ((last_note != note) || (last_play != play))
  {
    String status = note + play;
    char msg[8] = "note00s";
    status.toCharArray(msg,8);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();

    last_note = note;
    last_play = play;
  }

   if (debug) {
    delay(100);
   }

}

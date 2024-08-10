// Trent's pitch glove code
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Kalman.h> // Source: https://github.com/TKJElectronics/KalmanFilter

// Comment out to enable debugging
//#define DEBUG
//#define DEBUG2
//#define NOTRANSMIT

// Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf
//#define RESTRICT_PITCH

// Calibration Defaults
const float accXCal = 0.09;
const float accYCal = -0.29;
const float accZCal = -0.11;
const float gyroXCal = -0.03;
const float gyroYCal = 0.02;

// Create the mpu instance
Adafruit_MPU6050 mpu;

// Create the radio instance
RH_ASK driver(2000, 4, 5);

// Create the Kalman instances
Kalman kalmanX;
Kalman kalmanY;

/* IMU Data */
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
int16_t tempRaw;

double gyroXangle, gyroYangle; // Angle calculate using the gyro only
double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter

uint32_t timer;
double note_timer;

sensors_event_t a, g, temp;

// Remember previous note states
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
  mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
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

  mpu.getEvent(&a, &g, &temp);
  accX = a.acceleration.x + accXCal;
  accY = a.acceleration.y + accYCal;
  accZ = a.acceleration.z + accZCal;

#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double pitch  = atan2(accY, accZ) * RAD_TO_DEG;
  double roll = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double pitch  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double roll = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

  kalmanX.setAngle(roll); // Set starting angle
  kalmanY.setAngle(pitch);
  gyroXangle = roll;
  gyroYangle = pitch;
  
  timer = micros();
  note_timer = 0;
}


void loop() {

  /* Get new sensor events with the readings */
  mpu.getEvent(&a, &g, &temp);
  
  // Read accelerations
  accX = a.acceleration.x + accXCal;
  accY = a.acceleration.y + accYCal;
  accZ = a.acceleration.z + accZCal;

  gyroX = g.gyro.x + gyroXCal;
  gyroY = g.gyro.y + gyroYCal;
  gyroZ = g.gyro.z;

  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();
  note_timer = note_timer + dt;

  // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double pitch  = atan2(accY, accZ) * RAD_TO_DEG;
  double roll = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double pitch  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double roll = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

  //double gyroXrate = gyroX / 131.0; // Convert to deg/s
  //double gyroYrate = gyroY / 131.0; // Convert to deg/s
  double gyroXrate = gyroX * RAD_TO_DEG;
  double gyroYrate = gyroY * RAD_TO_DEG;

#ifdef RESTRICT_PITCH
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
    kalmanX.setAngle(roll);
    kalAngleX = roll;
    gyroXangle = roll;
  } else
    kalAngleX = kalmanX.getAngle(roll, gyroYrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleX) > 90)
    gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleY = kalmanY.getAngle(pitch, gyroXrate, dt);
#else
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
    kalmanY.setAngle(pitch);
    kalAngleY = pitch;
    gyroYangle = pitch;
  } else
    kalAngleY = kalmanY.getAngle(pitch, gyroXrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleY) > 90)
    gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleX = kalmanX.getAngle(roll, gyroYrate, dt); // Calculate the angle using a Kalman filter
#endif

  gyroXangle += gyroYrate * dt; // Calculate gyro angle without any filter
  gyroYangle += gyroXrate * dt;

  // Reset the gyro angle when it has drifted too much
  if (gyroXangle < -180 || gyroXangle > 180)
    gyroXangle = kalAngleX;
  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalAngleY;


  String note = last_note;
  double rotation = roll;
  if (note_timer > 0.2) {
    if (rotation > 82) note = "n01";
      else if (rotation > 62 and rotation < 78) note = "n02";
      else if (rotation > 42 and rotation < 58) note = "n03";
      else if (rotation > 22 and rotation < 38) note = "n04";
      else if (rotation > 2 and rotation < 18) note = "n05";
      else if (rotation > -18 and rotation < -2) note = "n06";
      else if (rotation > -38 and rotation < -22) note = "n07";
      else if (rotation > -58 and rotation < -42) note = "n08";
      else if (rotation > -78 and rotation < -62) note = "n09";
      else if (rotation <= -82) note = "n10";
      note_timer = 0;
  }
  //Serial.print("\nnote_timer :"); Serial.print(note_timer);

  // Show results 1
#ifdef DEBUG
  //Serial.print("\nroll: "); Serial.print(roll);
  Serial.print("\naccX: "); Serial.print(accX);
  //Serial.print("\tgyroAngleX: "); Serial.print(gyroXangle);
  //Serial.print("\tkalAngleX: "); Serial.print(kalAngleX);
  Serial.print("\tangleXrate: "); Serial.print(gyroX);
  //Serial.print("\tpitch: "); Serial.print(pitch);
  Serial.print("\taccY: "); Serial.print(accY);
  //Serial.print("\tgyroAngleY: "); Serial.print(gyroYangle);
  //Serial.print("\tkalAngleY: "); Serial.println(kalAngleY);
  Serial.print("\tangleYrate: "); Serial.print(gyroY);
  Serial.print("\taccZ: "); Serial.print(accZ);
#endif

  // Show results 2
#ifdef DEBUG2
  Serial.print(F("X Pitch: "));
  Serial.print(kalAngleY);
  Serial.print(F("\tY Roll: "));
  Serial.print(kalAngleX);
  Serial.print(F("\tNote: "));
  Serial.print(note);
  Serial.print(F("\tPlay: "));
#endif

  //Calculation experiments
  //float accel_ang_x = -atan2(ax,az)/2/3.141592654*360; 
  //float accel_ang_y = -atan2(ay,az)/2/3.141592654*360;
  //float accel_ang_x = atan2(ax,az)*180/3.141592654;
  //float pitch = atan2(-ax, sqrt(ay*ay + az*az))*180/3.141592654;
  //float roll = atan2(-ay,az)*180/3.141592654;

#ifndef NOTRANSMIT
  if (last_note != note)
  {
    String status = note;
    char *msg = "n00";
    status.toCharArray(msg,4);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.print("\nSent note: "); Serial.print(note);
  }
#endif

  last_note = note;
 
#ifdef DEBUG
   delay(100);
#endif

   delay(2);

}


#include <frequencyToNote.h>
#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>

// Trent's pitch glove code

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

int last_note = 0;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void stopnotes () {
  if (last_note == 1) {
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 2) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 3) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 4) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 5) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 6) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 7) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 8) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 57, 64);
    MidiUSB.flush();
    }

    
  if (last_note == 9) {
    noteOff(0, 44, 64);
    MidiUSB.flush();
    noteOff(0, 45, 64);
    MidiUSB.flush();
    noteOff(0, 47, 64);
    MidiUSB.flush();
    noteOff(0, 49, 64);
    MidiUSB.flush();
    noteOff(0, 50, 64);
    MidiUSB.flush();
    noteOff(0, 52, 64);
    MidiUSB.flush();
    noteOff(0, 54, 64);
    MidiUSB.flush();
    noteOff(0, 56, 64);
    MidiUSB.flush();
    }
  }

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

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

  Serial.println("");
  delay(100);
}

void noloop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");;
  delay(500);
}

void loop()
{

   /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // Read accelerations
  int ax = a.acceleration.x;
  int ay = a.acceleration.y;
  int az = a.acceleration.z;
  
  // mpu.getAcceleration(&ax, &ay, &az);
  //Calculate the angles of inclination
  float accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2)))*(180.0 / 3.14);
  float accel_ang_y = atan(ay / sqrt(pow(ax, 2) + pow(az, 2)))*(180.0 / 3.14);

  if (az < 0) {
    if (accel_ang_x < 0) {
      accel_ang_x = -180 - accel_ang_x;
    }
    else {
      accel_ang_x = 180 - accel_ang_x;
    }
    if (accel_ang_y < 0) {
      accel_ang_y = -180 - accel_ang_y;
    }
    else {
      accel_ang_y = 180 - accel_ang_y;
    }
  }
  // Show results
  //Serial.print(F("Inclination in X: "));
  //Serial.print(accel_ang_x);
  //Serial.print(F("\tY Tilt:"));
  //Serial.println(accel_ang_y);
  
  float roll = accel_ang_y;
  float pitch = accel_ang_x;


  
  if (roll > 80)
  {
    Serial.println("G#");
    stopnotes();
    noteOn(0, 44, 64);   // Channel 0, G#, normal velocity
    MidiUSB.flush();
    last_note = 1;
  }

  
  
  if (roll > 60 and roll < 80)
  {
    Serial.println("A");
    stopnotes();
    noteOn(0, 45, 64);   // Channel 0, A, normal velocity
    MidiUSB.flush();
    last_note = 2;
  }


  
  if (roll > 40 and roll < 60)
  {
    Serial.println("B");
    stopnotes();
    noteOn(0, 47, 64);   // Channel 0, B, normal velocity
    MidiUSB.flush();
    last_note = 3;
  }


  if (roll > 20 and roll < 40)
  {
    Serial.println("C#");
    stopnotes();
    noteOn(0, 49, 64);   // Channel 0, C#, normal velocity
    MidiUSB.flush();
    last_note = 4;
  }

  
  if (roll > 0 and roll < 20)
  {
    Serial.println("D");
    stopnotes();
    noteOn(0, 50, 64);   // Channel 0, D, normal velocity
    MidiUSB.flush();
    last_note = 5;
  }

  
  if (roll > -20 and roll < 0)
  {
    Serial.println("E");
    stopnotes();
    noteOn(0, 52, 64);   // Channel 0, E, normal velocity
    MidiUSB.flush();
    last_note = 6;
  }

  
  if (roll > -40 and roll < -20)
  {
    Serial.println("F#");
    stopnotes();
    noteOn(0, 54, 64);   // Channel 0, F#, normal velocity
    MidiUSB.flush();
    last_note = 7;
  }

  
  if (roll > -60 and roll < -40)
  {
    Serial.println("g#");
    stopnotes();
    noteOn(0, 56, 64);   // Channel 0, g#, normal velocity
    MidiUSB.flush();
    last_note = 8;
  }

  
  if (roll < -60)
  {
    Serial.println("a");
    stopnotes();
    noteOn(0, 57, 64);   // Channel 0, a, normal velocity
    MidiUSB.flush();
    last_note = 9;
  }
}

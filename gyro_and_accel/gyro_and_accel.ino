// Written by gday0

// connection
// Arduino  BMI160
// 3.3V     3V3
// GND      GND
// A4       SDA
// A5       SCL

#include <BMI160Gen.h>

const int i2c_addr = 0x69;

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
  // BMI160.begin(BMI160GenClass::SPI_MODE, select_pin);
  BMI160.begin(BMI160GenClass::I2C_MODE);

  BMI160.setGyroRange(250);
  BMI160.setAccelerometerRange(2);
  Serial.println("Initializing IMU device...done.");

}

void loop() {
  int axRaw, ayRaw, azRaw;
  int gxRaw, gyRaw, gzRaw;

  float ax, ay, az;
  float gx, gy, gz;

  BMI160.readMotionSensor(axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw);

  Serial.print("This is RAW data.\n");
  print(axRaw, ayRaw, azRaw, gxRaw, gyRaw, gzRaw);

  gx = convertRawGyro(gxRaw);
  gy = convertRawGyro(gyRaw);
  gz = convertRawGyro(gzRaw);

  ax = convertRawAccel(axRaw);
  ay = convertRawAccel(ayRaw);
  az = convertRawAccel(azRaw);

  Serial.print("This is converted data.\n");
  print(ax, ay, az, gx, gy, gz);

  delay(1000);
}

void print(int a, int b, int c, int d, int e, int f) {
  Serial.print("a:\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.print("g:\t");
  Serial.print(d);
  Serial.print("\t");
  Serial.print(e);
  Serial.print("\t");
  Serial.print(f);
  Serial.println();
 }

void print(float a, float b, float c, float d, float e, float f) {
  Serial.print("a:\t");
  Serial.print(a);
  Serial.print("\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.print(c);
  Serial.print("\t");
  Serial.print("g:\t");
  Serial.print(d);
  Serial.print("\t");
  Serial.print(e);
  Serial.print("\t");
  Serial.print(f);
  Serial.println();
 }

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * 250.0) / 32768.0;

  return g;
}

float convertRawAccel(int aRaw) {
  // since we are using 2 G range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float a = (aRaw * 2.0);

  return a;
}

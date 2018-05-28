// Modified by gday0
// Origin file is library exercise 'Gyro' in BMI160-Arduino-master.

// connection
// Arduino  BMI160
// 3.3V     3V3
// GND      GND
// A4       SDA
// A5       SCL

#include <BMI160Gen.h>
 
// const int select_pin = 10;
const int i2c_addr = 0x69;
 
void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open
 
  // initialize device
  Serial.println("Initializing IMU device...");
  // BMI160.begin(BMI160GenClass::SPI_MODE, select_pin);
  BMI160.begin(BMI160GenClass::I2C_MODE);

  BMI160.setGyroRange(250);
  Serial.println("Initializing IMU device...done.");
}
 
void loop() {
  int gxRaw, gyRaw, gzRaw;         // raw gyro values
  float gx, gy, gz;

  // read raw gyro measurements from device
  BMI160.readGyro(gxRaw, gyRaw, gzRaw);

  // convert the raw gyro data to degrees/second
  gx = convertRawGyro(gxRaw);
  gy = convertRawGyro(gyRaw);
  gz = convertRawGyro(gzRaw);

  // display tab-separated gyro x/y/z values
  Serial.print("g:\t");
  Serial.print(gx);
  Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.print(gz);
  Serial.println();

  delay(500);
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * 250.0) / 32768.0;

  return g;
}

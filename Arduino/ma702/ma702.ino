
//Check https://www.arduino.cc/en/reference/SPI for SPI signals connections

#define UART_BAUDRATE       115200        //UART data rate in bits per second (baud)
#define SPI_SCLK_FREQUENCY  300000        //SPI SCLK Clock frequency in Hz
#define SPI_CS_PIN          7             //SPI CS pin

MagAlpha magAlpha;

void setup() {
  // put your setup code here, to run once:
  //Set the SPI SCLK frequency, SPI Mode and CS pin
  // The frequency can go up to 10MHz, or even more, but the signal path must be very short.
  // If you plan to connect the sensor breakout using jumper wires, a frequence less than 1MHz is recommended.
  magAlpha.begin(SPI_SCLK_FREQUENCY, MA_SPI_MODE_3, SPI_CS_PIN);
  //Set the Serial Communication used to report the angle
  Serial.begin(UART_BAUDRATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  //========================================================================
  //Read the angle using different methods
  //========================================================================
  double angle;
  uint16_t angleRaw16;
  uint8_t angleRaw8;

  Serial.println("Read Angle using differents methods:");

  //Read the angle in degree (Read 16-bit raw angle value and then convert it to the 0-360 degree range)
  angle = magAlpha.readAngle();
  Serial.print("    magAlpha.readAngle() = ");
  Serial.println(angle, 3);

  //Read the angle (16-bit raw angle value)
  angleRaw16 = magAlpha.readAngleRaw();
  Serial.print("    magAlpha.readAngleRaw() = ");
  Serial.println(angleRaw16, DEC);

  //Read the angle (16-bit raw angle value), equivalent to magAlpha.readAngleRaw() function
  angleRaw16 = magAlpha.readAngleRaw16();
  Serial.print("    magAlpha.readAngleRaw16() = ");
  Serial.println(angleRaw16, DEC);

  //Read the angle (8-bit raw angle value)
  angleRaw8 = magAlpha.readAngleRaw8();
  Serial.print("    magAlpha.readAngleRaw8() = ");
  Serial.println(angleRaw8, DEC);

  //Read the angle (16-bit raw angle value) and check the parity bit to detect possible communication error
  bool error;
  angleRaw16 = magAlpha.readAngleRaw(&error);
  Serial.print("    magAlpha.readAngleRaw16(&error) = ");
  Serial.print(angleRaw16, DEC);
  if (error == true){
    Serial.print("\t => Communication error detected");
  }
  else{
    Serial.print("\t => Operation Succeed");
  }
  Serial.println();

  delay(1000);
}

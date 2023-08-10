void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  //set the resolution to 12 bits (0-4096)
  analogReadResolution(12);
}

void loop() {
  // read the analog / millivolts value for pin 2:

  // int analogValue = analogRead(4);
  // int analogVolts = analogReadMilliVolts(4);
  float voltage = analogToRealVoltage(analogReadMilliVolts(4));
  Serial.println(voltage);

  // Serial.println(analogReadMilliVolts(4));
  
  // print out the values you read:
  // Serial.printf("ADC analog value = %d\n",analogValue);
  // Serial.printf("ADC millivolts value = %d\n",analogVolts);
  
  delay(100);  // delay in between reads for clear read from serial
}

float analogToRealVoltage(int avoltage) {
  float x = avoltage/1000.0;
  float resistor1 = 4200;
  float resistor2 = 4300;
  float voltage_divider = (resistor2 / (resistor1+resistor2));
  return x/(voltage_divider);
}
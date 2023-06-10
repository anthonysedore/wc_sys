#include <SoftwareSerial.h>

#define MYPORT_TX 26
#define MYPORT_RX 27

EspSoftwareSerial::UART myPort;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Standard hardware serial port
  myPort.begin(9600, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  if (!myPort) { // If the object did not initialize, then its configuration is invalid
    Serial.println("Invalid EspSoftwareSerial pin configuration, check config"); 
    while (1) { // Don't continue with invalid configuration
      delay (1000);
    }
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {        // If anything comes in Serial (USB),
    myPort.write(Serial.read());  // read it and send it out Serial1 (pins 0 & 1)
  }

  if (myPort.available()) {       // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(myPort.read());  // read it and send it out Serial (USB)
  }
}
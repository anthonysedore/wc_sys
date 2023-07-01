#include <Arduino.h>
#include "wc_sys_GPS.h"
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
EspSoftwareSerial::UART myPort;

void startGPS() {
  myPort.begin(9600, SWSERIAL_8N1, GPS_RX, GPS_TX, false);
}

void getCoord(float *coordinates) {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (myPort.available())
    {
      char c = myPort.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
	coordinates[0] = flat;
	coordinates[1] = flon;
  }
  if (chars == 0) {
    Serial.println("** No characters received from GPS: check wiring **");
  }
}


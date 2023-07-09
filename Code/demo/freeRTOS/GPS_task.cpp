#include "GPS_task.h"

TinyGPS gps;
EspSoftwareSerial::UART myPort;

float latitude, longitude;
unsigned long gps_date, gps_time, age;

void setupGPS() {
  // put your setup code here, to run once:
  myPort.begin(9600, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);
  if (!myPort) { // If the object did not initialize, then its configuration is invalid
    Serial.println("Invalid EspSoftwareSerial pin configuration, check config"); 
    while (1) { // Don't continue with invalid configuration
      //delay (1000);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  } 
}

void loopGPS(void *parameter) {
  while (1) {
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
      gps.f_get_position(&latitude, &longitude, &age);
    }
    
    gps.stats(&chars, &sentences, &failed);

    if (chars == 0) {
      Serial.println("** No characters received from GPS: check wiring **");
    }
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

void updateTime() {
  gps.get_datetime(&gps_date, &gps_time);
}
#include "wc_sys_GPS.h"

float long_lat[2];

void setup() {
  // put your setup code here, to run once:
  startGPS();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  getCoord(long_lat);
  delay(1000);
  Serial.print("LAT: ");
  Serial.println(long_lat[0]);
  Serial.print("Long: ");
  Serial.println(long_lat[1]);
}

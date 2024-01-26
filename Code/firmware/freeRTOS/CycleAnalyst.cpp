#include "Arduino.h"

void setupCA() {
  Serial2.begin(9600, SERIAL_8N1, 14, 13); //14, 13 For using with USB Cable
  //Serial2.begin(9600, SERIAL_8N1, 13, 14); //13, 14 For using with Cycle Analyst
}

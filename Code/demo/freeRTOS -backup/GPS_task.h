#ifndef GPS_task_H_
#define GPS_task_H_

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define MYPORT_TX 26
#define MYPORT_RX 27

// Variables
extern float latitude, longitude;
extern unsigned long age;

//  function prototypes
void setupGPS();
void loopGPS(void *parameter);

#endif /* GPS_task_H_ */

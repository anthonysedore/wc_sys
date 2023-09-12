#ifndef GPS_task_H_
#define GPS_task_H_

#include "Arduino.h"
#include "Definitions.h"
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define MYPORT_TX 6
#define MYPORT_RX 7

//  function prototypes
void setupGPS();
void loopGPS(void *parameter);
void updateTime();

#endif /* GPS_task_H_ */

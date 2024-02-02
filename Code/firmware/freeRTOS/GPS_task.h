#ifndef GPS_task_H_
#define GPS_task_H_

#include "Arduino.h"
#include "Definitions.h"
#include <TinyGPS.h>

#define MYPORT_TX 26
#define MYPORT_RX 27

//  function prototypes
void setupGPS();
void loopGPS(void *parameter);
void updateTime();

#endif /* GPS_task_H_ */

#ifndef DATA_task_H_
#define DATA_task_H_

#include "Arduino.h"
#include "Definitions.h"
#include "GPS_task.h"
#include "CycleAnalyst_task.h"
#include <ESP32Time.h> //For keeping time in RTC

extern int dateANDtime[6];

//  function prototypes
void loopDATA(void *parameter);

#endif /* DATA_task_H_ */

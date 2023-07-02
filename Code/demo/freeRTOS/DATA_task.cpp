#include "DATA_task.h"

//DATA Task should start after being called by either physical button or touchscreen
//For future, would like to add auto start using car velocity

void loopDATA(void *parameter) {
  updateTime();
  //date is ddmmyy, time is hhmmss ms
  char filename[30];
  sprintf(filename, "%lu.%lu", gps_date, gps_time-4000000); //-4000000 to adjust time to Eastern Time
  Serial.println(filename);

  stopwatch = 0;
  while (1) {
    Serial.println(stopwatch++);
    vTaskDelay(1000 / portTICK_PERIOD_MS); //Counts 1 second
  }
}


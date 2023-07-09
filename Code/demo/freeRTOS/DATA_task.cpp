#include "DATA_task.h"
#include "SDscript.h"

//DATA Task should start after being called by either physical button or touchscreen
//For future, would like to add auto start using car velocity

int dateANDtime[6]; //Date and time arrray, (30, 24, 15, 17, 1, 2021);  // 17th Jan 2021 15:24:30
ESP32Time rtc(-18000);
float dataTime = 0.0;

//decodetime horrible method to get time
//replace with void crack_datetime(int *year, byte *month, byte *day, 
//    byte *hour, byte *minute, byte *second, byte *hundredths = 0, unsigned long *fix_age = 0);
void decodeTime()
{
    //char pointer declaration
    char temp[7];
    char temp2[9]; //temp2 used for time
    //assig number as string in char pointer
    sprintf((char*)temp,"%lu", gps_date);

    

    //Shifts string 1 to the right, to fix format
    if (strlen(temp)==5) {
      for(int i=6; i>0; i--)
        temp[i] = temp[i-1];
      temp[0] = '0';
    }

    dateANDtime[3] = (temp[0] - 48) * 10 + (temp[1] - 48); //Day of Month
    dateANDtime[4] = (temp[2] - 48) * 10 + (temp[3] - 48); //Month
    dateANDtime[5] = (temp[4] - 48) * 10 + (temp[5] - 48) + 2000; //Year
    sprintf((char*)temp2,"%lu", gps_time);
    dateANDtime[0] = (temp2[0] - 48) * 10 + (temp2[1] - 48); //Hour of Day
    dateANDtime[1] = (temp2[2] - 48) * 10 + (temp2[3] - 48); //Minutes
    dateANDtime[2] = (temp2[4] - 48) * 10 + (temp2[5] - 48); //Seconds, don't need milliseconds

    Serial.println(dateANDtime[3]);
    Serial.println(dateANDtime[4]);
    Serial.println(dateANDtime[5]);
    Serial.println("Time:");
    Serial.println(dateANDtime[0]);
    Serial.println(dateANDtime[1]);
    Serial.println(dateANDtime[2]);
}

void loopDATA(void *parameter) 
{
  SDsetup();
  while (1) {
    if (dataActive) {
      dataTime = 0.0;
      updateTime();
      char filename[30];
      char dataEntry[40];
      //date is ddmmyy, time is hhmmss ms
      decodeTime();
      sprintf(filename, "/%lu.%lu.csv", gps_date, gps_time-4000000); //-4000000 to adjust time to Eastern Time
      //rtc.setTime(30, 24, 15, gps_date, 1, 2021);
      Serial.println(filename);


      rtc.setTime(dateANDtime[2], dateANDtime[1], dateANDtime[0], dateANDtime[3], dateANDtime[4], dateANDtime[5]);

      listDir(SD, "/", 0);

      writeFile(SD, filename, "# RaceRender Data\n");
      appendFile(SD, filename, "Time,Lap,Latitude,Longitude,MPH\n");

      while (dataActive) {
        sprintf(dataEntry, "%.2f,0,%.6f,%.6f,0\n", dataTime, latitude, longitude);
        appendFile(SD, filename, dataEntry);
        dataTime = dataTime+0.1;
        vTaskDelay(100 / portTICK_PERIOD_MS);
        // Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); 
      }
    }
  //END OF LOOP, loop ending, save data below and suspend task until called again


  vTaskSuspend(NULL); //NULL means task suspends itself
  }
}
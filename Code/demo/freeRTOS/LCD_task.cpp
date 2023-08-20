#include "LCD_task.h"

hw_timer_t * timer2 = NULL; //Used for the fake readings such as speed

TFT_eSPI tft = TFT_eSPI();

void setupLCD() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_YELLOW);
  timer2 = timerBegin(0, 80, true);
}

void updateLCD(void *parameter) {
  while (1) {
    tft.setCursor(0, 0, 4);

    //Display Coordinates
    tft.setTextColor(TFT_WHITE, TFT_BLACK); tft.setTextFont(4);
    tft.print("Latitude = ");
    tft.println(latitude, 6);
    tft.print("Longitude = ");
    tft.println(longitude, 6);

    tft.print("MPH (speed) = ");
    tft.println(checkSpeed(), 2); //Display 2 decimals for float

    tft.print("Battery Voltage = ");
    tft.println(checkBatteryVoltage(), 2); //Display 2 decimals for float
    
    //Display Recording Time, changes text color for when recording starts and stops
    tft.setCursor(0, 100, 4);
    if (dataActive) {
      tft.setTextColor(TFT_GREEN, TFT_BLACK); tft.setTextFont(4);
    } else {
      tft.setTextColor(TFT_RED, TFT_BLACK); tft.setTextFont(4);
    }
    
    //Display time of recording
    tft.println("Recording Time = ");
    tft.println(dataTime);
    
    //Waits 100ms then updates screen again
    vTaskDelay(100 / portTICK_PERIOD_MS); //End Screen
  }
}

//Used for fake measurements to test display
float checkSpeed(void) {
  float speed;
  double time = timerReadSeconds(timer2);
  speed = 5*cos(time*0.2)-0.5*sin(time*0.5)+20;
  return speed; 
}

float checkBatteryVoltage(void) {
  float voltage;
  double time = timerReadSeconds(timer2);
  voltage = 84-0.05*time;
  return voltage; 
}

//I don't use this
void loopTouch(void *parameter) {
  while (1) {
    vTaskDelay(50 / portTICK_PERIOD_MS); //Checks every 50 ms for touch input
  }
}

//I don't use this either
// Print the header for a display screen
void header(const char *string)
{
  tft.setTextSize(1);
  tft.setTextColor(TFT_MAGENTA, TFT_BLUE);
  tft.fillRect(0, 0, 480, 30, TFT_BLUE);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(string, 239, 2, 4); // Font 4 for fast drawing with background
}

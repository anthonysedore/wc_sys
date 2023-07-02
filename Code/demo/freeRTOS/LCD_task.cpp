#include "LCD_task.h"

TFT_eSPI tft = TFT_eSPI();

// Print the header for a display screen
void header(const char *string)
{
  tft.setTextSize(1);
  tft.setTextColor(TFT_MAGENTA, TFT_BLUE);
  tft.fillRect(0, 0, 480, 30, TFT_BLUE);
  tft.setTextDatum(TC_DATUM);
  tft.drawString(string, 239, 2, 4); // Font 4 for fast drawing with background
}

void setupLCD() {
  tft.init();

  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void updateLCD(void *parameter) {
  while (1) {
    tft.fillScreen(TFT_NAVY); // Clear screen to navy background
    
    //header("Print eSPI Test");

    tft.setCursor(0, 0, 4);

    //Display Coordinates
    tft.setTextColor(TFT_WHITE, TFT_BLACK); tft.setTextFont(4);
    tft.print("Latitude = ");
    tft.println(latitude, 6);
    tft.print("Longitude = ");
    tft.println(longitude, 6);

    //Display Recording Time
    tft.setCursor(0, 100, 4);
    if (toggleDATA) {
      tft.setTextColor(TFT_GREEN, TFT_BLACK); tft.setTextFont(4);
    } else {
      tft.setTextColor(TFT_RED, TFT_BLACK); tft.setTextFont(4);
    }
    
    tft.println("Recording Time = ");
    tft.println(stopwatch);
    

    vTaskDelay(1000 / portTICK_PERIOD_MS); //End Screen
  }
}

void loopTouch(void *parameter) {
  while (1) {
    vTaskDelay(50 / portTICK_PERIOD_MS); //Checks every 50 ms for touch input
  }
}
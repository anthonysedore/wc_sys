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

  int h = tft.height();
  int w = tft.width();

  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void updateLCD(void *parameter) {
  while (1) {
    int xpos =  0;
    int ypos = 40;

    tft.fillScreen(TFT_NAVY); // Clear screen to navy background
    
    //header("Print eSPI Test");

    tft.setCursor(0, 0, 4);
    
    tft.setTextColor(TFT_WHITE, TFT_BLACK); tft.setTextFont(4);
    tft.print("Latitude = ");
    tft.println(latitude, 6);
    tft.print("Longitude = ");
    tft.println(longitude, 6);

    

    vTaskDelay(10000 / portTICK_PERIOD_MS); //End Screen
  }
}

#include "GPS_task.h"
#include "LCD_task.h"

void displayGPS(void *parameter) {
  while (1) {
    Serial.print("Latitude = ");
    Serial.print(latitude, 6);
    Serial.print(", Longitude = ");
    Serial.println(longitude, 6);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Debug serial port
  setupGPS();
  setupLCD();

  // xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
  //             loopGPS,  // Function to be called
  //             "Update GPS Values",   // Name of task
  //             1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
  //             NULL,         // Parameter to pass to function
  //             2,            // Task priority (0 to configMAX_PRIORITIES - 1) //Higher number = more priority
  //             NULL,         // Task handle
  //             1);     // Run on one core for demo purposes (ESP32 only)

  xTaskCreatePinnedToCore(loopGPS, "Update GPS", 1024, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(displayGPS, "Display GPS", 1024, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(updateLCD, "Send screen to LCD", 4096, NULL, 1, NULL, 0); //RUNS ON SECOND CORE :)))
}

void loop() {
  
}


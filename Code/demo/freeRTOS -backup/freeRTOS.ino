#include "GPS_task.h"
#include "LCD_task.h"

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

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
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
              loopGPS,  // Function to be called
              "Update GPS Values",   // Name of task
              1024,         // Stack size (bytes in ESP32, words in FreeRTOS)
              NULL,         // Parameter to pass to function
              2,            // Task priority (0 to configMAX_PRIORITIES - 1) //Higher number = more priority
              NULL,         // Task handle
              1);     // Run on one core for demo purposes (ESP32 only)

  xTaskCreatePinnedToCore(displayGPS, "Display GPS", 1024, NULL, 1, NULL, 1);

  xTaskCreatePinnedToCore(updateLCD, "Send screen to LCD", 1024, NULL, 1, NULL, 0); //RUNS ON SECOND CORE :)))

}

void loop() {
  //loopGPS();
  //vTaskDelay(1 / portTICK_PERIOD_MS)
}


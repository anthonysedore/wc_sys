#include "Definitions.h" //Contains Global Variables
#include "GPS_task.h" //Contains GPS functions
#include "LCD_task.h" //Responsible for LCD display
#include "DATA_task.h" //Responsible keep track of data and logging to SD Card
#include "WIRELESS_task.h" //Responsible for communicating to base station

bool dataActive = false;

static TaskHandle_t taskDATA = NULL; 

void setup() {
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
  xTaskCreatePinnedToCore(loopDATA, "starts datalog", 10240, NULL, 4, &taskDATA, 1);
  xTaskCreatePinnedToCore(updateLCD, "Send screen to LCD", 4096, NULL, 1, NULL, 0); //RUNS ON SECOND CORE :)))
}

void loop() {
  checkTouchPin();
  vTaskDelay(50 / portTICK_PERIOD_MS); //Check button every 50 milliseconds
}

void checkTouchPin() {
  if (touchRead(1) < 35) {
    dataActive = !dataActive;
    if (dataActive) {
      vTaskResume(taskDATA);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

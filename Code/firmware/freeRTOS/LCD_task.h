#ifndef LCD_task_H_
#define LCD_task_H_

#include "Arduino.h"
#include "Definitions.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "CycleAnalyst_task.h"
//#include "Free_Fonts.h" // Include the header file attached to this sketch


//  function prototypes
void setupLCD();
void updateLCD(void *parameter);
void header(const char *string);
void loopTouch(void *parameter);

#endif /* LCD_task_H_ */

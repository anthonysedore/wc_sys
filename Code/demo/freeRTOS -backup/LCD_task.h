#ifndef LCD_task_H_
#define LCD_task_H_

#include "Arduino.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#define BLACK 0x0000
#define WHITE 0xFFFF


//  variables


//  function prototypes
void setupLCD();
void updateLCD(void *parameter);
void lcd_run();
void RenderImage( void);
void SetVars(void);
void ProcessLine(struct Line2d *ret, struct Line3d vec);
void cube(void);


#endif /* LCD_task_H_ */

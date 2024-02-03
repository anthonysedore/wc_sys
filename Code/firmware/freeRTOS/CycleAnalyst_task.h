#ifndef CycleAnalyst_task_H_
#define CycleAnalyst_task_H_

#include "Arduino.h"

#define CA_AH 0
#define CA_V 1
#define CA_A 2
#define CA_S 3
#define CA_D 4
#define CA_DEG 5
#define CA_RPM 6
#define CA_HW 7
#define CA_NM 8
#define CA_THI 9
#define CA_THO 10
#define CA_AUXA 11
#define CA_AUXD 12
#define CA_FLGS 13

// Variables
extern char CA_data[14][8];
extern bool newData;

//  function prototypes
void printCA();
void setupCA();
void encodeCA(Stream &CAserial);
void loopCA(void *parameter);

#endif /* CycleAnalyst_task_H_ */

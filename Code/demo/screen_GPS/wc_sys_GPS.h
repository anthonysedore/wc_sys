#ifndef wc_sys_GPS_H_
#define wc_sys_GPS_H_

//#include "Arduino.h"

#define GPS_TX 26
#define GPS_RX 27

//  function prototypes
void startGPS();
void getCoord(float *coordinates);

#endif /* wc_sys_GPS_H_ */

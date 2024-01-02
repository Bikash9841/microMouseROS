#ifndef Sensor_H
#define Sensor_H
#include <VL53L0X.h>

// address we will assign if dual sensor is present
#define rightAddress 0x30
#define frontAddressRight 0x31
#define frontAddressLeft 0x32
#define leftAddress 0x33

// set the pins to shutdown
#define xshutRight PA8
#define xshutFrontRight PB5
#define xshutFrontLeft PB8
#define xshutLeft PB9

#define right 0
#define frontRight 1
#define frontLeft 2
#define left 3


extern bool F;
extern bool R;
extern bool L;

extern uint16_t dist[4];
extern uint16_t distOld[4];

extern VL53L0X sensor[4];

void setID();
void read_quad_sensors();
//void checkDevice();/
void printDistance();
void detectWalls();
void wallsInfo();

#endif

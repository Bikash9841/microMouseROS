#ifndef MOTOR_H
#define MOTOR_H


#include <Arduino.h>
#include "Maze.h"

#define eLeft PA7
#define eRight  PA2
#define fLeft PA6
#define bLeft  PA5
#define bRight PA4
#define fRight  PA3
#define Renc1 PB0
#define Lenc1 PA1
#define Renc2 PB1
#define Lenc2 PA0

extern bool flag;
extern float pwmd;
extern float pwmr;
extern float pwms;

extern float lmpwm;
extern float rmpwm;

extern volatile int16_t ticksL;
extern volatile int16_t ticksR;

extern int16_t finalTick;
extern int16_t avTicks;

void setPID();

void countTicksL();
void countTicksR();
void moveForward(float distance);
void stopbot();
void turnRight();
void turnLeft();
void uTurn();
void moveFS(float distance);
void motorMotion(int16_t lpwm,int16_t rpwm);

#endif

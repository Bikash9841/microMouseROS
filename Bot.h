
#ifndef BOT_H
#define BOT_H

#include <Arduino.h>

extern int16_t botx, boty, botxP, botyP, preV;
extern int16_t botx0, boty0, botx1, boty1, botx2, boty2, botx3, boty3;

extern int8_t orient;

extern bool flag;
extern uint8_t count;

void updateCoordinates(int16_t *botx, int16_t *boty, int8_t orient);
void orientation(int8_t *orient, char turning);

#endif

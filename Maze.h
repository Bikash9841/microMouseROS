#ifndef MAZE_H
#define MAZE_H


#include "Bot.h"
#include "Queue.h"

extern uint8_t cells[16][16];
extern uint16_t flood[16][16];

extern uint8_t i; //for loop iterator

extern int16_t minVal;
extern int16_t maxVal;
extern int8_t minCell, noMovements; //used to determine which direction to move
extern char turning;                        // use to update the orientation of mouse

//used in isConsistant function
extern int16_t floodVal;
extern int16_t minVals[4];
extern uint8_t minCount;

// --------------------------------------------------------------------------

void getSurrounds(int16_t botx, int16_t boty, int16_t *botx0, int16_t *boty0, int16_t *botx1, int16_t *boty1,
                  int16_t *botx2, int16_t *boty2, int16_t *botx3, int16_t *boty3);

void updateWalls(int16_t botx, int16_t boty, int8_t orient,
                 bool L, bool R, bool F);

bool isAccessible(int16_t botx, int16_t boty, int16_t givx, int16_t givy);

char toMove(int16_t botx, int16_t boty, int16_t botxP, int16_t botyP, int8_t orient);
char toMoveFast(int16_t botx, int16_t boty, int16_t botxP, int16_t botyP, int8_t orient);

bool isConsistant(int16_t botx, int16_t boty);
void makeConsistant(int16_t botx, int16_t boty);
void floodfill(int16_t botx, int16_t boty);
void floodfill2();
void appendDestination(int16_t botx,int16_t boty);
void appendZero();


#endif

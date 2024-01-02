#include "Bot.h"

int16_t botx=0; 
int16_t boty=0; 
int16_t botxP=0;
int16_t botyP=0;
int16_t preV; 
int16_t botx0, boty0, botx1, boty1, botx2, boty2, botx3, boty3=0;
int8_t orient=0;
bool flag = true;
uint8_t count=0;

void updateCoordinates(int16_t *botx, int16_t *boty, int8_t orient)
{

    if (orient == 0)
    {
        *boty += 1;
    }
    if (orient == 1)
    {
        *botx += 1;
    }
    if (orient == 2)
    {
        *boty -= 1;
    }
    if (orient == 3)
    {
        *botx -= 1;
    }
}

void orientation(int8_t *orient, char turning)
{
    if (turning == 'L')
    {
        *orient -= 1;

        if (*orient == -1)
        {
            *orient = 3;
        }
    }
    else if (turning == 'R')
    {
        *orient += 1;
        if (*orient == 4)
        {
            *orient = 0;
        }
    }
    else if (turning == 'B')
    {
        if (*orient == 0)
        {
            *orient = 2;
        }
        else if (*orient == 1)
        {
            *orient = 3;
        }
        else if (*orient == 2)
        {
            *orient = 0;
        }
        else if (*orient == 3)
        {
            *orient = 1;
        }
    }
}

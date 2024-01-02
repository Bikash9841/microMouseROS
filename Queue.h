
#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>
#define MAX 260

extern int16_t avail;
extern int16_t p;
extern bool overflow;
extern bool underflow;
extern int16_t delval;


typedef struct
{
    int16_t info, next;
}
nodetype;

typedef struct
{
    int16_t front = -1;
    int16_t rear = -1;
}
queue;

extern queue q;
extern nodetype node[MAX];

void initialise();
int16_t getnode();
void freenode(int16_t p);
void enqueue(int16_t a);
int16_t dequeue();

#endif

#include "Queue.h"

int16_t avail = 0;
int16_t p;
bool overflow=false;
bool underflow=false;
int16_t delval;

nodetype node[MAX];
queue q;

void initialise()
{
    for (int16_t i = 0; i < MAX - 1; i++)
    {
        node[i].next = i + 1;
    }
    node[MAX - 1].next = -1;
}

int16_t getnode()
{
    if (avail == -1)
    {
        overflow=true;
    }
    p = avail;
    avail = node[avail].next;
    return p;
}


void freenode(int16_t p)
{
    node[p].next = avail;
    avail = p;
}



void enqueue(int16_t a)
{
    int16_t ptr;
    ptr = getnode();
    node[ptr].info = a;
    node[ptr].next = -1;
    if (q.rear == -1)
    {
        q.front = ptr;
    }
    else
    {
        node[q.rear].next = ptr;
    }
    q.rear = ptr;
}


int16_t dequeue()
{
    int16_t ptr;
    if (q.front == -1)
    {
       underflow=true;
    }
    else
    {
        delval = node[q.front].info;
        ptr = q.front;
        q.front = node[q.front].next;
        if (q.front == -1)
        {
            q.rear = -1;
        }
        freenode(ptr);
        return delval;
    }
}

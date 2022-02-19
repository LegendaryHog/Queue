#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY_0 8
#define NULL_PTR_EXIT if (que == NULL){return ERR;}

typedef double data_t;

typedef struct
{
    data_t* data;
    size_t  head;
    size_t  tail;
    size_t  capacity;
    size_t  size;
    char    ctored;
}
queue;

enum ERRORS{
    ERR    = 0,
    NO_ERR = 1,
};

enum MODES{
    UP,
    DOWN,
};



int    Q_Ctor       (queue* que);
int    Q_Dtor       (queue* que);
int    Q_Resize     (queue* que, int mode);
int    Q_Push_Front (queue* que, data_t push);
int    Q_Push_Back  (queue* que, data_t push);
data_t Q_Pop_Front  (queue* que);
data_t Q_Pop_Back   (queue* que);
int    Q_Dump       (queue* que);

#endif
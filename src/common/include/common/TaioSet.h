#ifndef __TAIOSET_H__
#define __TAIOSET_H__

#include <stdio.h>

typedef struct TaioSet
{
    char* Name;
    int* Numbers;
    int Count;
} TaioSet;

void PrintSet(TaioSet* set);
#endif
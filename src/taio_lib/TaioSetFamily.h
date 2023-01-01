#ifndef __TAIOSETFAMILY_H__
#define __TAIOSETFAMILY_H__

#include "TaioSet.h"

typedef struct TaioSetFamily{
    TaioSet** Sets;
    int SetCount;
}TaioSetFamily;

void PrintSetFamily(TaioSetFamily * family);
#endif
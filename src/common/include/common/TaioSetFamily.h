#ifndef __TAIOSETFAMILY_H__
#define __TAIOSETFAMILY_H__

#include "common/TaioSet.h"

typedef struct TaioSetFamily{
    TaioSet** Sets;
    int SetCount;
}TaioSetFamily;

void PrintSetFamily(TaioSetFamily * family);
#endif
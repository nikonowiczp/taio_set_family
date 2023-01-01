#ifndef __TAIODATA_H__
#define __TAIODATA_H__

#include "TaioSetFamily.h"

typedef struct TaioData{
    TaioSetFamily* Family1;
    TaioSetFamily* Family2;
}TaioData;

void PrintData(TaioData* data);
#endif

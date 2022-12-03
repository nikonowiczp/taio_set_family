#ifndef __TAIODATA_H__
#define __TAIODATA_H__

#include "common/TaioSetFamily.h"

typedef struct TaioData{
    TaioSetFamily* Family1;
    TaioSetFamily* Family2;
}TaioData;

void printData(TaioData* data);
#endif
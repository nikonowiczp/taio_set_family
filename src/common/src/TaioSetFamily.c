#include "common/TaioSetFamily.h"

void PrintSetFamily(TaioSetFamily * family){
    printf(" Family has %d sets \n", family->SetCount);
    for( int i =0; i< family->SetCount; i++){
        printf(" Set %d - %d member(s): \n", i+1, family->Sets[i]->Count);
        PrintSet(family->Sets[i]);
    }
}
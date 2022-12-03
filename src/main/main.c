#include "set_parser/SetParser.h"
#include "common/TaioData.h"
#include <stdio.h>

TaioSetFamily* prepareFirstTestFamily();
TaioSetFamily* prepareSecondTestFamily();

int main (int argc, char *argv[]){
    printf("Hello world from C");
    // example taio family. modify if needed
    TaioSetFamily* family1 = prepareFirstTestFamily();
    TaioSetFamily* family2 =prepareSecondTestFamily();
    TaioData data;
    data.Family1 = family1;
    data.Family2 = family2;

    return 0;
}

TaioSetFamily* prepareFirstTestFamily(){
    TaioSetFamily* family1 = (TaioSetFamily*) malloc(sizeof(TaioSetFamily));

    family1->SetCount = 3;
    TaioSet* set1 = (TaioSet *) malloc (sizeof(TaioSet));
    TaioSet* set2 = (TaioSet *) malloc (sizeof(TaioSet));
    TaioSet* set3 = (TaioSet *) malloc (sizeof(TaioSet));
    family1->Sets = (TaioSet**) malloc(sizeof(TaioSet)*3);
    family1->Sets[0] = set1;
    family1->Sets[1] = set2;
    family1->Sets[2] = set3;
    set1->Count = 1;
    

    return family1;
}

TaioSetFamily* prepareSecondTestFamily(){
    TaioSetFamily* family2 = (TaioSetFamily*) malloc(sizeof(TaioSetFamily));
    return family2;
}
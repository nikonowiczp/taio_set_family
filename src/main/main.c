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
    set1->Count = 3;
    set1->Numbers = (int*) malloc (sizeof(int)*3);
    set1->Numbers[0] = 1;
    set1->Numbers[1] = 2;
    set1->Numbers[2] = 3;
    TaioSet* set2 = (TaioSet *) malloc (sizeof(TaioSet));
    set1->Count = 3;
    set2->Numbers = (int*) malloc (sizeof(int)*3);
    set2->Numbers[0] = 2;
    set2->Numbers[1] = 5;
    set2->Numbers[2] = 6;
    TaioSet* set3 = (TaioSet *) malloc (sizeof(TaioSet));
    set1->Count = 4;
    set3->Numbers = (int*) malloc (sizeof(int)*4);
    set3->Numbers[0] = 1;
    set3->Numbers[1] = 4;
    set3->Numbers[2] = 8;
    set3->Numbers[3] = 12;

    family1->Sets = (TaioSet**) malloc(sizeof(TaioSet)*3);
    family1->Sets[0] = set1;
    family1->Sets[1] = set2;
    family1->Sets[2] = set3;
    

    return family1;
}

TaioSetFamily* prepareSecondTestFamily(){
    TaioSetFamily* family1 = (TaioSetFamily*) malloc(sizeof(TaioSetFamily));
    
    family1->SetCount = 2;
    TaioSet* set1 = (TaioSet *) malloc (sizeof(TaioSet));
    set1->Count = 1;
    set1->Numbers = (int*) malloc (sizeof(int)*1);
    set1->Numbers[0] = 7;
    TaioSet* set2 = (TaioSet *) malloc (sizeof(TaioSet));
    set1->Count = 2;
    set2->Numbers = (int*) malloc (sizeof(int)*2);
    set2->Numbers[0] = 2;
    set2->Numbers[1] = 9;

    family1->Sets = (TaioSet**) malloc(sizeof(TaioSet)*2);
    family1->Sets[0] = set1;
    family1->Sets[1] = set2;
    
    return family1;
}
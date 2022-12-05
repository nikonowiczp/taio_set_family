#ifndef __TAIOSETLIST_H__
#define __TAIOSETLIST_H__

#include "common/TaioSet.h"

typedef struct TaioSetListElement
{
    TaioSet* Set;
    TaioSet* Next;
} TaioSetListElement;

typedef struct TaioSetList
{
    TaioSetListElement* Head;
    TaioSetListElement* Tail;
    int elemNum;
} TaioSetList;

void PrintSetList(TaioSetList*);
void PrintSetListElement(TaioSetListElement*, int);
void InsertFirst(TaioSetList*, TaioSet*);
void InsertLast(TaioSetList*, TaioSet*);
void FreeList(TaioSetList*);
TaioSetList* CreateList();
#endif
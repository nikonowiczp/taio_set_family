#include "common/TaioSetList.h"

void PrintSetListElement(TaioSetListElement* listElement, int i){
    printf(" Set no. %d: %s\n", i, listElement->Set->Name);

}

void PrintSetList(TaioSetList* list) {
    printf("Printing SetList with %d elements:\n", list->elemNum);

    if(list->Head) {
         TaioSetListElement* p = list->Head;
        int i = 0;
        while(p) {
            PrintSetListElement(p, i++);
            p = p->Next;
        }
    }
}

TaioSetList* CreateList() {
    TaioSetList *list = (TaioSetList *)malloc(sizeof(TaioSetList));
    list->elemNum = 0;
    list->Head = NULL;
    list->Tail = NULL;

    return list;
}

void InsertFirst(TaioSetList* list, TaioSet* set) {
    if(list == NULL || set == NULL)
        return;

    TaioSetListElement *p = (TaioSetListElement *)malloc(sizeof(TaioSetListElement));
    p->Set = set;
    p->Next = list->Head;

    if(list->Head == NULL) {
        list->elemNum = 1;
        list->Head = p;
        list->Tail = p;
    }
    else {
        list->Head = p;
        list->elemNum++;
    }
}

void InsertLast(TaioSetList* list, TaioSet* set) {
    if(list == NULL || set == NULL)
        return;

    TaioSetListElement *p = (TaioSetListElement *)malloc(sizeof(TaioSetListElement));
    p->Set = set;
    p->Next = NULL;
    
    if(list->Head == NULL) {
        list->Head = p;
        list->Tail = p;
        list->elemNum = 1;
    }
    else {
        list->Tail->Next = p;
        list->Tail = p;
        list->elemNum++;
    }
}

void FreeList(TaioSetList* list) {
    if(list->Head); {
        TaioSetListElement *p = list->Head;
        TaioSetListElement *prev;
        while(p) {
            prev = p;
            p = p->Next;
            free(prev->Set);
            free(prev);
        }
    }
}
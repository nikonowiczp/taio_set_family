#include "common/TaioSet.h"

void PrintSet(TaioSet* set){
    if(DEBUG) printf("  Set name is \"%s\".\n", set->Name);
    if(set->Count == 0 )return;
    printf(" ");
    for(int i = 0; i < set->Count; i++){
        printf(" %d", set->Numbers[i]);
    }
    printf("\n");

}

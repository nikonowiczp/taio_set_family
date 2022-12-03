#include "common/TaioSet.h"


void PrintSet(TaioSet* set){
    printf(" Set name is \"%s\"\n", set->Name);
    for(int i = 0; i<set->Count; i++){
        printf("  %d \n", set->Numbers[i]);
    }
}

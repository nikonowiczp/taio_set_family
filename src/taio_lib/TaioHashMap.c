#include "TaioHashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
TaioSet* GetSetFromString(char* line);

HashMap *InitializeHashMap(){
    HashMap* map = (HashMap *) malloc(sizeof(HashMap));

    hashmap_init(map, hashmap_hash_string, strcmp);
    return map;
}
TaioData* GetReducedFamilyData(HashMap* map, TaioData* data){
    for(int i =0;i<data->Family1->SetCount; i++){
        AddFamily1Set(map, data->Family1->Sets[i]);
    }

    for(int i =0;i<data->Family2->SetCount; i++){
        AddFamily2Set(map, data->Family2->Sets[i]);
    }
    TaioData *newData = (TaioData*) malloc(sizeof(TaioData));

    GenerateSets(map, newData);
    return newData;
}

void GenerateSets(HashMap* map, TaioData* newData){
    int family1Count=0, family2Count = 0;
    newData->Family1 = (TaioSetFamily*) malloc(sizeof(TaioSetFamily));
    newData->Family2 = (TaioSetFamily*) malloc(sizeof(TaioSetFamily));
    newData->Family1->SetCount = 0;
    newData->Family2->SetCount = 0;
    const char *key;
    int val;

    hashmap_foreach(key, val, map) {
        if(val > 0 )newData->Family1->SetCount += val;
        if(val < 0 )newData->Family2->SetCount -= val;
    }

    newData->Family1->Sets = (TaioSet*) malloc (sizeof(TaioSet)*newData->Family1->SetCount);
    newData->Family2->Sets = (TaioSet*) malloc (sizeof(TaioSet)*newData->Family2->SetCount);

    if(DEBUG) printf("\n\n\nHashmap dump \n\n\n");

    if(DEBUG) {
        hashmap_foreach(key, val, map) {
        printf("Key \"%s\" value: %d\n", key, val);
    }
    }
    if(DEBUG) printf("\n\n\nAfter hashmap dump \n\n\n");

    hashmap_foreach(key, val, map) {
        if(((int)val) > 0 ){
            for(int i = 0; i < val; i++){
                newData->Family1->Sets[family1Count] = GetSetFromString(key);
                family1Count+=1;
            }
        }
        if( ((int)val) < 0 ){
            for(int i =0; i < -1*val; i++){
                newData->Family2->Sets[family2Count] = GetSetFromString(key);
                family2Count+=1;
            }
        }
    }
    if(DEBUG) printf("End generate sets\n");

    return newData;
}
TaioSet* GetSetFromString(char* line){
    if(DEBUG) printf("Get set from string \"%s\"\n", line);
    if(DEBUG) printf("boo\n");
    TaioSet* set = (TaioSet*) malloc(sizeof(TaioSet));
    if(DEBUG) printf("Before string malloc\n");

    char *pch;

    char *tmpLine = (char *)malloc(sizeof(char) * (strlen(line) + 1));
    strcpy(tmpLine, line);
    pch = strtok(tmpLine, " ");
    set->Count = atoi(pch);
    if(DEBUG) printf("Set has count %d\n", set->Count);

    if (set->Count < 0)
    {
        printf("Set count is smaller than 0");
        exit(EXIT_FAILURE);
    }
    set->Numbers = (int *)malloc(sizeof(int) * set->Count);
    set->Name = (char *)malloc(sizeof(char) * strlen(line)+1);

    strcpy(set->Name, line);
    for (int i = 0; i < set->Count; i++)
    {
        pch = strtok(NULL, " ");
        if (pch == NULL)
        {
            printf("Set number not found");
            exit(EXIT_FAILURE);
        }
        set->Numbers[i] = atoi(pch);
        if(DEBUG) printf("Parsed number %d\n", set->Numbers[i]);

    }
    free(tmpLine);
    if(DEBUG) printf("End generate string\n");

    return set;
}
void FreeHashMap(HashMap* map){
    hashmap_cleanup(map);
}

void AddFamily1Set(HashMap* map, TaioSet *set){
    int val = hashmap_get(map, set->Name);
    if(val == NULL){
        int result = hashmap_put(map, set->Name, 1);
    }else if(val == -1){
        val = hashmap_remove(map, set->Name);
    }else{
        val = hashmap_remove(map, set->Name);
        int result = hashmap_put(map, set->Name, val+1);
    }

}
void AddFamily2Set(HashMap* map, TaioSet* set){

    int val = hashmap_get(map, set->Name);
    if(val == NULL){
        int result = hashmap_put(map, set->Name, -1);
    }else if(val == 1){
        val = hashmap_remove(map, set->Name);
    }else{
        val = hashmap_remove(map, set->Name);
        int result = hashmap_put(map, set->Name, val-1);
    }

}

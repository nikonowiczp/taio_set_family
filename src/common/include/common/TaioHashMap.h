#ifndef __TAIOHASHMAP_H__
#define __TAIOHASHMAP_H__

#include "hashmap.h"
#include "TaioData.h"

typedef HASHMAP(char, int) HashMap;


HashMap* InitializeHashMap();
TaioData* GetReducedFamilyData(HashMap* map, TaioData* data);

void FreeHashMap(HashMap* map);
void AddFamily1Set(HashMap* map, TaioSet *set);
void AddFamily2Set(HashMap* map, TaioSet* set);
#endif
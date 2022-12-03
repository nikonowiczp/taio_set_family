#include "set_parser/SetParser.h"
#include "common/TaioData.h"
#include "common/TaioHashMap.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    TaioData *parsedData, *reducedData;
    HashMap *map;
    if(argc < 2){
        printf("Please provide path to parse set");
        exit(EXIT_FAILURE);
    }
    parsedData = parseData(argv[1]);
    printf("\n\nData read\n\n");

    PrintData(parsedData);
    map = InitializeHashMap();
    reducedData = GetReducedFamilyData(map, parsedData);
    printf("\n\nData after reduction\n\n");
    PrintData(reducedData);
    FreeHashMap(map);

    return 0;
}
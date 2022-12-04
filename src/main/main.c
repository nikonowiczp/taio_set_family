#include "set_parser/SetParser.h"
#include "common/TaioData.h"
#include "common/TaioHashMap.h"
#include <stdio.h>
#include <stdlib.h>

int MetricTwo(HashMap* dictionary);


int main (int argc, char *argv[]){
    TaioData *parsedData, *reducedData;
    HashMap *map;
    int metric2;
    if(argc < 2){
        printf("Please provide path to parse set");
        exit(EXIT_FAILURE);
    }
    parsedData = parseData(argv[1]);
    printf("\n\nData read\n\n");

    PrintData(parsedData);
    map = InitializeHashMap();
    printf("\n\nReducing data\n\n");
    reducedData = GetReducedFamilyData(map, parsedData);
    printf("\n\nData after reduction\n\n");
    PrintData(reducedData);

    printf("\n\nEasy algorithm\n\n");
    metric2 = MetricTwo(map);
    printf("\n\nCalculated metric = %d\n", metric2);

    FreeHashMap(map);

    return 0;
}

int MetricTwo(HashMap* dictionary){
    int ab = 0, ba = 0;
    const char *key;
    int val;
    printf("Starting metric two\n");

    hashmap_foreach(key, val, dictionary) {
        if (val > 0){
            ab += val;
        }
        else if (val < 0){
            ba += (-1)*val;
        }
    }

    return ab+ba;
}
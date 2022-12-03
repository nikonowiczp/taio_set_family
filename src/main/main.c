#include "set_parser/SetParser.h"
#include "common/TaioData.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
    TaioData *parsedData;

    if(argc < 2){
        printf("Please provide path to parse set");
        exit(EXIT_FAILURE);
    }
    parsedData = parseData(argv[1]);
    PrintData(parsedData);

    return 0;
}
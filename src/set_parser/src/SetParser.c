#include "set_parser/SetParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
TaioData* parseData(char* filename){
    FILE * fp;
    char * tmp;
    TaioData * data = (TaioData* )malloc(sizeof(TaioData));
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("File could not be opened");
        exit(EXIT_FAILURE);
    }
    printf("Parsing data from file %s\n", filename);
    printf("Parsing family 1\n");
    data->Family1 = parseFamily(fp);
    printf("Parsing family 2\n");
    data->Family2 = parseFamily(fp);
    fclose(fp);
    return data;
}

TaioSetFamily* parseFamily(FILE * fp){
    TaioSetFamily* family = (TaioSetFamily *)malloc(sizeof(TaioSetFamily));
    size_t read;
    char * line = NULL;
    size_t len = 0;
    if((read = getline(&line, &len, fp)) == -1){
        printf("Error reading line");
        exit(EXIT_FAILURE);
    }
    family->SetCount = atoi(line);
    printf("Family has %d sets\n", family->SetCount);
    if(family-> SetCount < 0 ){
        printf("Set count less than 0");
        exit(EXIT_FAILURE);        
    }
    family->Sets = (TaioSet*) malloc (sizeof(TaioSet)*family->SetCount);
    for(int i =0; i < family->SetCount; i++){
        if((read = getline(&line, &len, fp)) == -1){
            printf("Error reading line");
            exit(EXIT_FAILURE);
        }
        family->Sets[i] = parseSet(line);
    }

    if (line)
        free(line);

    return family;
}
TaioSet* parseSet(char* line){
    TaioSet* set = (TaioSet*) malloc(sizeof(TaioSet));
    printf("Parsing set %s\n", line);
    char* tmpLine = (char* ) malloc(sizeof(char)*(strlen(line)+1));

    strcpy(tmpLine, line);
    char * pch;

    printf ("Splitting string \"%s\" into tokens:\n",tmpLine);
    pch = strtok (tmpLine," ");
    set->Count = atoi(pch);
    if(set->Count < 0){
        printf("Set count is smaller than 0");
        exit(EXIT_FAILURE);
    } 
    set->Numbers = (int*) malloc(sizeof(int)*set->Count);

    for(int i =0; i< set->Count; i++){
        pch = strtok (NULL," ");
        if(pch == NULL){
            printf("Set number not found");
            exit(EXIT_FAILURE);
        }
        set->Numbers[i] = atoi(pch);
    }
    free(tmpLine);
    return set;
}
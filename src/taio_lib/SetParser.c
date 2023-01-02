#include "SetParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* ltrim(char *s);
char* rtrim(char *s);
char* trim(char *s);
void GenerateName(TaioSet* set);
void SortArray(int* numbers, int count);
TaioData *parseData(char *filename)
{
    FILE *fp;
    char *tmp;
    TaioData *data = (TaioData *)malloc(sizeof(TaioData));
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File could not be opened");
        exit(EXIT_FAILURE);
    }
    if(DEBUG) printf("Parsing data from file %s\n", filename);
    if(DEBUG) printf("Parsing family 1\n");
    data->Family1 = parseFamily(fp);
    if(DEBUG) printf("Parsing family 2\n");
    data->Family2 = parseFamily(fp);
    fclose(fp);
    return data;
}

TaioSetFamily *parseFamily(FILE *fp)
{
    TaioSetFamily *family = (TaioSetFamily *)malloc(sizeof(TaioSetFamily));
    size_t read;
    char line[MAX_LENGTH];
    size_t len = 0;
    if (!fgets(line, MAX_LENGTH, fp))
    {
        printf("Error reading line");
        exit(EXIT_FAILURE);
    }
    family->SetCount = atoi(line);
    if(DEBUG) printf("Family has %d sets\n", family->SetCount);
    if (family->SetCount < 0)
    {
        printf("Set count less than 0");
        exit(EXIT_FAILURE);
    }
    family->Sets = (TaioSet *)malloc(sizeof(TaioSet) * family->SetCount);
    for (int i = 0; i < family->SetCount; i++)
    {
        if (!fgets(line, MAX_LENGTH, fp))
        {
            printf("Error reading line");
            exit(EXIT_FAILURE);
        }
        family->Sets[i] = parseSet(line);
    }

    return family;
}

TaioSet *parseSet(char *line)
{
    TaioSet *set = (TaioSet *)malloc(sizeof(TaioSet));
    if(DEBUG) printf("Parsing set %s\n", line);
    char *tmpLine = (char *)malloc(sizeof(char) * (strlen(line) + 1));

    strcpy(tmpLine, line);
    char *pch;

    if(DEBUG) printf("Splitting string \"%s\" into tokens:\n", tmpLine);
    pch = strtok(tmpLine, " ");
    set->Count = atoi(pch);
    if (set->Count < 0)
    {
        printf("Set count is smaller than 0");
        exit(EXIT_FAILURE);
    }
    set->Numbers = (int *)malloc(sizeof(int) * set->Count);
    set->Name = (char *)malloc(sizeof(char) * (strlen(line)+1));

    strcpy(set->Name, line);
    set->Name = trim(set->Name);
    for (int i = 0; i < set->Count; i++)
    {
        pch = strtok(NULL, " ");
        if (pch == NULL)
        {
            printf("Set number not found");
            exit(EXIT_FAILURE);
        }
        set->Numbers[i] = atoi(pch);
    }
    SortArray(set->Numbers, set->Count);
    GenerateName(set);
    free(tmpLine);
    return set;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

void itoa_new(char* buffer, int number){
    snprintf(buffer, sizeof(buffer), "%d", number);

}
void GenerateName(TaioSet* set){
    char *buffer = (char*)malloc(sizeof(char)*(strlen(set->Name)+1));
    int currentNameIndex = 0;
    if(DEBUG) printf("Regenerating name");
    itoa_new(buffer, set->Count);
    for(int j =0; j<strlen(buffer); j++){
            set->Name[currentNameIndex]=buffer[j];
            currentNameIndex++;
    }
    if (set->Count > 0){
        set->Name[currentNameIndex] = ' ';
        currentNameIndex++;
    }
    for(int i=0; i<set->Count; i++){
        itoa_new(buffer, set->Numbers[i]);

        for(int j =0; j<strlen(buffer); j++){
            set->Name[currentNameIndex]=buffer[j];
            currentNameIndex++;
        }
        if( i <set->Count -1){
            set->Name[currentNameIndex] = ' ';
            currentNameIndex++;
        }

    }
    set->Name[currentNameIndex] = '\0';
    if(DEBUG) printf("New name is \"%s\"", set->Name);

    free(buffer);
}
int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

void SortArray(int* numbers, int count){
    qsort( numbers, count, sizeof(int), compare );
}

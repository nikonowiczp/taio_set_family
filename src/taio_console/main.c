#include "SetParser.h"
#include "TaioData.h"
#include "TaioHashMap.h"
#include "TaioSetList.h"
#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "taioalgorithms.h"
#include "SetRunner.h"

#define MAXPATH 2048
#define MAXRUNNERPATHS 32

void printLineToOutput(const char * format, ...);
void outputToFile(char* outputFolder, char* fileName);

int currentLine = 0;
char *lines[MAXRUNNERPATHS];

int main (int argc, char *argv[]){
    int metric = 0;
    char cont = 'Y';
    char* path;
    char output_directory[MAXPATH];

    if(argc == 2 && strcmp(argv[1], "-h") == 0){
        printf("This program will launch in interactive mode if run without any parameters.\n"
                "If run with parameters it will try to parse every file provided as argument.\n"
                "In that case every metric will be printed to stdouut.\n");
        exit(EXIT_SUCCESS);
    }

    if(argc > 1){
        if(argc == 2){
            printf("In order to launch this program in non-interactive mode provide output directory as the first argument\n"
                              "Rest of the arguments will should be paths to input files");
            exit(EXIT_FAILURE);
        }
        if(!strcpy(output_directory, argv[1])){
            printf("Error while copying outtput directory");
            exit(EXIT_FAILURE);
        }
        for(int i =2; i<argc; i++){
            RunSet(argv[i], METRIC_ALL, printLineToOutput);
            outputToFile(output_directory , argv[i]);
        }
        exit(EXIT_SUCCESS);
    }
    path =(char*)malloc(sizeof(char)*MAXPATH);
    printf("\n\nPlease choose output folder for files\n");
    scanf("%s", output_directory);


    while(cont == 'y' || cont == 'Y') {
        printf("Please input path to the text file with data: ");
        scanf("%s", path);

        printf("Please choose which metric to use: \n");
        printf("1. Iteration with Jaccard metric.\n");
        printf("2. Sum of a difference.\n");
        printf("3. Iteration with Jaccard metric and sum of a difference.\n");
        printf("4. Intuitive metric.\n");
        printf("5. Aproximated intuitive metric.\n");
        printf("6. All.\n");
        scanf("%d", &metric);
        currentLine = 0;
        switch(metric){
            case 1:
                RunSet(path, METRIC_ONE, printLineToOutput);
                break;
            case 2:
                RunSet(path, METRIC_TWO, printLineToOutput);
                break;
            case 3:
                RunSet(path, METRIC_ONE | METRIC_TWO , printLineToOutput);

                break;
            case 4:
                RunSet(path, METRIC_THREE, printLineToOutput);
                break;
            case 5:
                RunSet(path, METRIC_FOUR, printLineToOutput);

                break;
            case 6:
                RunSet(path, METRIC_ALL, printLineToOutput);
                break;

            default:
                printf("Sorry, I don't understand.\n");
        }
        outputToFile(output_directory , path);
        printf("\n\nWould you like to calculate metrics for another file (Y/N)? ");
        scanf(" %c", &cont);
    }

    return 0;
}
void printLineToOutput(const char * format, ...){
    char* buffer = (char*) malloc(sizeof(char)*MAXPATH);
    va_list argptr;
    va_start(argptr, format);
    vsprintf(buffer, format, argptr);
    lines[currentLine] = buffer;
    currentLine += 1;
    printf(buffer);
    va_end(argptr);
}

void outputToFile(char* outputFolder, char* fileName){
    FILE *fp, *inFp;
    char *tmp;
    char outputFileName[MAX_LENGTH], *inputBaseName;
    char line[MAX_LENGTH];
    size_t len = 0;
    //TODO make outputFile name
    inputBaseName = basename(fileName);
    int i =0;

    inFp = fopen(fileName, "r");
    if (inFp == NULL)
    {
        printf("Input file could not be opened");
        exit(EXIT_FAILURE);
    }

    while(inputBaseName[i] != '.' && inputBaseName[i]!='\0'){
        i++;
    }
    inputBaseName[i] = '\0';

    sprintf(outputFileName, "%s/%s.out.txt", outputFolder, inputBaseName);

    fp = fopen(outputFileName, "w");
    printf("Writing data to file %s\n", outputFileName);

    if (fp == NULL)
    {
        printf("Output file could not be opened");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<currentLine; i++){
        fputs(lines[i], fp);
    }
    fputs("\n", fp);


    while (fgets(line, MAX_LENGTH, inFp) != NULL)
    {
        fputs(line, fp);
    }
    fclose(inFp);

    fclose(fp);

    for(int i =0;i<currentLine; i++){
        free(lines[i]);
    }
    currentLine = 0;
    return ;
}

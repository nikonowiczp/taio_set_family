#include "SetParser.h"
#include "TaioData.h"
#include "TaioHashMap.h"
#include "TaioSetList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "taioalgorithms.h"
#define MAXPATH 128
#include "SetRunner.h"

void printLineToOutput(const char * format, ...);

int main (int argc, char *argv[]){
    int metric = 0;
    char cont = 'Y';
    char* path;


    if(argc == 2 && strcmp(argv[1], "-h") ==0){
        printLineToOutput("This program will launch in interactive mode if run without any parameters.\n"
                "If run with parameters it will try to parse every file provided as argument.\n"
                "In that case every metric will be printed to stdouut.\n");
        exit(EXIT_SUCCESS);
    }

    if(argc > 1){
        for(int i =1; i<argc; i++){
            RunSet(argv[i], METRIC_ALL, printLineToOutput);
        }
        exit(EXIT_SUCCESS);
    }
    path =(char*)malloc(sizeof(char)*MAXPATH);
    while(cont == 'y' || cont == 'Y') {
        printLineToOutput("Please input path to the text file with data: ");
        scanf("%s", path);

        printLineToOutput("Please choose which metric to use: \n");
        printLineToOutput("1. Iteration with Jaccard metric.\n");
        printLineToOutput("2. Sum of a difference.\n");
        printLineToOutput("3. Iteration with Jaccard metric and sum of a difference.\n");
        printLineToOutput("4. Intuitive metric.\n");
        printLineToOutput("5. Aproximated intuitive metric.\n");
        printLineToOutput("6. All.\n");
        scanf("%d", &metric);

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
                printLineToOutput("Sorry, I don't understand.\n");
        }

        printLineToOutput("\n\nWould you like to calculate metrics for another file (Y/N)? ");
        scanf(" %c", &cont);
    }

    return 0;
}
void printLineToOutput(const char * format, ...){
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stdout, format, argptr);
    va_end(argptr);
}

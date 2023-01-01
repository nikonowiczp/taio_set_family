#include "SetParser.h"
#include "TaioData.h"
#include "TaioHashMap.h"
#include "TaioSetList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "taioalgorithms.h"
#define MAXPATH 128


int main (int argc, char *argv[]){
    TaioData *parsedData, *reducedData;
    HashMap *map;             
    clock_t start, end;
    float seconds;
    int metric = 0;
    double metricValue;
    char cont = 'Y';
    char* path;


    if(argc == 2 && strcmp(argv[1], "-h") ==0){
        printf("This program will launch in interactive mode if run without any parameters.\n"
                "If run with parameters it will try to parse every file provided as argument.\n"
                "In that case every metric will be printed to stdouut.\n");
        exit(EXIT_SUCCESS);
    }

    if(argc > 1){
        for(int i =1; i<argc; i++){
                printf("\n\nCalculating metric for file %s\n\n", argv[i]);
                start = clock();

                parsedData = parseData(argv[i]);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;
                printf("Parsing data took  %.8f seconds\n", seconds);

                if(DEBUG) PrintData(parsedData);
                map = InitializeHashMap();

                start = clock();
                reducedData = GetReducedFamilyData(map, parsedData);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;
                printf("Generating hash map and reducing data took %.8f seconds\n", seconds);

                if(DEBUG) PrintData(reducedData);

                printf("\nMetric as iteration with Jaccard metric:\n");
                start = clock();
                metricValue = MetricOne(map);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;

                printf("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);

                printf("\nMetric as sum of a difference:\n");
                start = clock();
                metricValue = MetricTwo(map);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;
                printf("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);

                printf("\nIntuitive metric:\n");
                start = clock();
                metricValue = MetricThree(map, parsedData);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;
                printf("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);

                printf("\nApproximated intuitive metric:\n");
                start = clock();
                metricValue = MetricThreeApprox(map, parsedData);
                end = clock();
                seconds = (float)(end - start) / CLOCKS_PER_SEC;
                printf("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);
                FreeHashMap(map);

        }
        exit(EXIT_SUCCESS);
    }
    path =(char*)malloc(sizeof(char)*MAXPATH);
    while(cont == 'y' || cont == 'Y') {
        printf("Please input path to the text file with data: ");
        scanf("%s", path);

        printf("Please choose which metric to use (1/2/3): \n");
        printf("1. Iteration with Jaccard metric.\n");
        printf("2. Sum of a difference.\n");
        printf("4. Intuitive metric.\n");
        printf("5. Aproximated intuitive metric.\n");
        printf("6. All.\n");
        scanf("%d", &metric);

        parsedData = parseData(path);
        if(DEBUG) printf("\n\nData read\n\n");

        if(DEBUG) PrintData(parsedData);
        map = InitializeHashMap();
        if(DEBUG) printf("\n\nReducing data\n\n");
        reducedData = GetReducedFamilyData(map, parsedData);
        if(DEBUG) printf("\n\nData reduced\n\n");
        PrintData(reducedData);

        switch(metric){
            case 1:
                metricValue = MetricOne(map);
                printf("Calculated metric = %.2f\n", metricValue);
                break;
            case 2:
                metricValue = MetricTwo(map);
                printf("Calculated metric = %.0f\n", metricValue);
                break;
            case 3:
                printf("\nMetric as iteration with Jaccard metric:\n");
                metricValue = MetricOne(map);
                printf("Calculated metric = %.2f\n", metricValue);
                printf("\nMetric as sum of a difference:\n");
                metricValue = MetricTwo(map);
                printf("Calculated metric = %.0f\n", metricValue);
                break;
            case 4:
                printf("\nIntuitive metric:\n");
                metricValue = MetricThree(map, parsedData);
                printf("Calculated metric = %.2f\n", metricValue);
                break;
            case 5:
                printf("\nApproximated intuitive metric:\n");
                metricValue = MetricThreeApprox(map, parsedData);
                printf("Calculated metric = %.2f\n", metricValue);
                break;
            case 6:
                printf("\nMetric as iteration with Jaccard metric:\n");
                metricValue = MetricOne(map);
                printf("Calculated metric = %.2f\n", metricValue);

                printf("\nMetric as sum of a difference:\n");
                metricValue = MetricTwo(map);
                printf("Calculated metric = %.0f\n", metricValue);

                printf("\nIntuitive metric:\n");
                metricValue = MetricThree(map, parsedData);
                printf("Calculated metric = %.2f\n", metricValue);

                printf("\nApproximated intuitive metric:\n");
                metricValue = MetricThreeApprox(map, parsedData);
                printf("Calculated metric = %.2f\n", metricValue);

                break;
            default:
                printf("Sorry, I don't understand.\n");
        }

        FreeHashMap(map);
        printf("\n\nWould you like to calculate metrics for another file (Y/N)? ");
        scanf(" %c", &cont);
    }

    return 0;
}

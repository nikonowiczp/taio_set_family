#include "SetRunner.h"
#include "SetParser.h"
#include "TaioData.h"
#include "TaioHashMap.h"
#include "TaioSetList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "taioalgorithms.h"
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))


void RunSet(char* filePath, int metricsToRun, void (*printLineToOutput)(const char * format, ...)){
    TaioData *parsedData, *reducedData;
    HashMap *map;
    clock_t start, end;
    float seconds;
    int metric = 0;
    double metricValue;
    char* path;
    printLineToOutput("\n\nCalculating metric for file %s\n\n", filePath);
    start = clock();

    parsedData = parseData(filePath);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printLineToOutput("Parsing data took  %.8f seconds\n", seconds);

    if(DEBUG) PrintData(parsedData);
    map = InitializeHashMap();

    start = clock();
    reducedData = GetReducedFamilyData(map, parsedData);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printLineToOutput("Generating hash map and reducing data took %.8f seconds\n", seconds);

    if(DEBUG) PrintData(reducedData);

    if(metricsToRun & METRIC_ONE){
        printLineToOutput("\nMetric as iteration with Jaccard metric:\n");
        start = clock();
        metricValue = MetricOne(map);
        end = clock();
        seconds = (float)(end - start) / CLOCKS_PER_SEC;

        printLineToOutput("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);

    }

    if(metricsToRun & METRIC_TWO){
        printLineToOutput("\nMetric as sum of a difference:\n");
        start = clock();
        metricValue = MetricTwo(map);
        end = clock();
        seconds = (float)(end - start) / CLOCKS_PER_SEC;

        printLineToOutput("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);
    }

    if(metricsToRun & METRIC_THREE){
        printLineToOutput("\nIntuitive metric:\n");
        start = clock();
        metricValue = MetricThree(map, parsedData);
        end = clock();
        seconds = (float)(end - start) / CLOCKS_PER_SEC;

        printLineToOutput("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);
    }

    if(metricsToRun & METRIC_FOUR){
        printLineToOutput("\nApproximated intuitive metric:\n");
        start = clock();
        metricValue = MetricThreeApprox(map, parsedData);
        end = clock();
        seconds = (float)(end - start) / CLOCKS_PER_SEC;

        printLineToOutput("Calculated metric = %.2f. It took  %.8f seconds\n", metricValue, seconds);
    }

    FreeHashMap(map);
}

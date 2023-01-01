#ifndef SETRUNNER_H
#define SETRUNNER_H
#define METRIC_ONE 1
#define METRIC_TWO 2
#define METRIC_THREE 4
#define METRIC_FOUR 8
#define METRIC_ALL METRIC_ONE | METRIC_TWO | METRIC_THREE | METRIC_FOUR

void RunSet(char* filePath, int metricsToRun, void (*printLineToOutput)(const char * format, ...));

#endif // SETRUNNER_H

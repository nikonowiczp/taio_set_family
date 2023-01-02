#ifndef __SETPARSER_H__
#define __SETPARSER_H__
#define MAX_LENGTH 32768
#include "TaioData.h"


TaioData* parseData(char* filename);
TaioSetFamily* parseFamily(FILE * fp);
TaioSet* parseSet(char* line);
#endif

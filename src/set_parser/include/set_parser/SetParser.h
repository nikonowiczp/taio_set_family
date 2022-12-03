#ifndef __SETPARSER_H__
#define __SETPARSER_H__

#include "common/TaioData.h"

TaioData* parseData(char* filename);
TaioSetFamily* parseFamily(FILE * fp);
TaioSet* parseSet(char* line);
#endif
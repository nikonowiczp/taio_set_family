#ifndef __SETPARSER_H__
#define __SETPARSER_H__

#include "common/TaioData.h"

typedef struct SetParser{

}SetParser;

TaioData* parseData(char* filename);
TaioSetFamily* parseFamily(SetParser parser);
TaioSet* parseSet(SetParser parser);
#endif
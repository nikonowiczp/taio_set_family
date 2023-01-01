#ifndef TAIOALGORITHMS_H
#define TAIOALGORITHMS_H

#include "TaioHashMap.h"
#include "TaioSetList.h"

int MetricOne(HashMap*);
int MetricTwo(HashMap*);
void PrepareLists(TaioSetList*, TaioSetList*, HashMap*);
double IterateSets(TaioSetList*, TaioSetList*);
double J(TaioSet*, TaioSet*);

TaioSet* FamilyToSet(TaioSetFamily*);
int SetToBin(TaioSet*);

double MetricThree(HashMap*, TaioData*);
double MetricThreeApprox(HashMap*, TaioData*);
int CountOnes(int);

double AlternativeMetric(TaioData*);

#endif // TAIOALGORITHMS_H

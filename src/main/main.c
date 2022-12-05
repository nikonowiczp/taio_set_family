#include "set_parser/SetParser.h"
#include "common/TaioData.h"
#include "common/TaioHashMap.h"
#include "common/TaioSetList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPATH 25

int MetricOne(HashMap*);
int MetricTwo(HashMap*);
void PrepareLists(TaioSetList*, TaioSetList*, HashMap*);
double IterateSets(TaioSetList*, TaioSetList*);
double J(TaioSet*, TaioSet*);

TaioSet* FamilyToSet(TaioSetFamily*);
int SetToBin(TaioSet*);
double AlternativeMetric(TaioData*);

double CrazyMetric(TaioData*);
int CountOnes(int);

int main (int argc, char *argv[]){
    TaioData *parsedData, *reducedData;
    HashMap *map;
    int metric = 0;
    double metricValue;
    char cont = 'Y';
    char* path =(char*)malloc(sizeof(char)*MAXPATH);

    while(cont == 'y' || cont == 'Y') {
        printf("Please input path to the text file with data: ");
        scanf("%s", path);

        printf("Please choose which metric to use (1/2/3): \n");
        printf("1. Iteration with Jaccard metric.\n");
        printf("2. Sum of a difference.\n");
        printf("3. Both.\n");
        scanf("%d", &metric);

        parsedData = parseData(path);
        printf("\n\nData read\n\n");

        PrintData(parsedData);
        map = InitializeHashMap();
        printf("\n\nReducing data\n\n");
        reducedData = GetReducedFamilyData(map, parsedData);
        printf("\n\nData reduced\n\n");
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
                printf("\nMetric as simple Jaccard distance between sets:\n");
                metricValue = AlternativeMetric(parsedData);
                printf("Calculated metric = %.2f\n", metricValue);
                break;
            case 5:
                printf("\nMetric as crazy Jaccard distance between sets:\n");
                metricValue = CrazyMetric(parsedData);
                printf("Calculated metric = %.2f\n", metricValue);
                break;
            case 6:
                printf("\nMetric as iteration with Jaccard metric:\n");
                metricValue = MetricOne(map);
                printf("Calculated metric = %.2f\n", metricValue);

                printf("\nMetric as sum of a difference:\n");
                metricValue = MetricTwo(map);
                printf("Calculated metric = %.0f\n", metricValue);

                printf("\nMetric as simple Jaccard distance between sets:\n");
                metricValue = AlternativeMetric(parsedData);
                printf("Calculated metric = %.2f\n", metricValue);

                printf("\nMetric as crazy Jaccard distance between sets:\n");
                metricValue = CrazyMetric(parsedData);
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

int MetricTwo(HashMap* dictionary){
    int ab = 0, ba = 0;
    const char *key;
    int val;

    hashmap_foreach(key, val, dictionary) {
        if (val > 0){
            ab += val;
        }
        else if (val < 0){
            ba += (-1)*val;
        }
    }

    return ab+ba;
}

int MetricOne(HashMap* dictionary) {
    TaioSetList *listA = CreateList();
    TaioSetList *listB = CreateList();

    PrepareLists(listA, listB, dictionary);

    double res = IterateSets(listA, listB);

    FreeList(listA);
    FreeList(listB);

    return res;
}

void PrepareLists(TaioSetList* listA, TaioSetList* listB, HashMap* dictionary) {
    const char *key;
    int val;
    hashmap_foreach(key, val, dictionary) {
        char *tmp = (char *)malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(tmp, key);

        if (val > 0) {
            for(int i = 0; i < val; i++) {
                InsertLast(listA, parseSet(tmp));
            }
        }
        else if (val < 0){
            for(int i = 0; i > val; i--) {
                InsertLast(listB, parseSet(tmp));
            }
        }

        if(tmp)
            free(tmp);
    }
}

double IterateSets(TaioSetList *A, TaioSetList *B) {
    double sum = 0;
    if(A->elemNum == 0)
        return B->elemNum;
    if(B->elemNum == 0)
        return A->elemNum;

    TaioSetListElement *X = A->Head;
    while(X) {
        TaioSetListElement *Y = B->Head;
        while(Y) {
            sum += 1 - J(X->Set, Y->Set);
            Y = Y->Next;
        }
        X = X->Next;
    }

    return sum;
}

double J(TaioSet* X, TaioSet* Y) {
    int cut = 0;

    for(int i_x = 0; i_x < X->Count; i_x++) {
        for(int i_y = 0; i_y < Y->Count; i_y++) {
            if(X->Numbers[i_x] == Y->Numbers[i_y]) {
                cut++;
                break;
            }
        }
    }

    double sum = X->Count + Y->Count - cut;
    return cut/sum;
}

// konwertuje rodzinę na zbiór liczb
TaioSet* FamilyToSet(TaioSetFamily* family) {
    TaioSet *set = (TaioSet *)malloc(sizeof(TaioSet));

    set->Count = family->SetCount;
    set->Numbers = (int *)malloc(sizeof(int) * set->Count);

    for(int i = 0; i < set->Count; i++) {
        set->Numbers[i] = SetToBin(family->Sets[i]);
    }

    return set;
}

// konwertuje zbiór na liczbę binarną (gdy zbiór zawiera liczbę 4, to liczba binarna ma 1 na bin[3])
int SetToBin(TaioSet* set) {
    int bin = 0;

    for(int i = 0; i < set->Count; i++) {
        bin |= 1 << (set->Numbers[i] - 1);
    }

    return bin;
}

// oblicza prostą odległość jaccarda między zbiorami
double AlternativeMetric(TaioData* data) {
    TaioSet* A = FamilyToSet(data->Family1);
    TaioSet* B = FamilyToSet(data->Family2);

    double jDist = 1 - J(A, B);

    free(A->Numbers);
    free(A);
    free(B->Numbers);
    free(B);

    return jDist;
}

// konwetuje rodzinę na zbiór liczb binarnych
// porównując każdy zbiór z każdym (aka każdy zbiór w rodzinie z każdym)
// zlicza ile dane liczby binarne mają takich samych 'jedynek' a ile różnych (aka zlicza ile każdy zbiór ma wspólnych elementów i ile różniących się)
// metryka to 1 - (suma_ile_takich_samych / suma_ile_różniących_się) / (wszystkie jedynki)
double CrazyMetric(TaioData* data) {
    TaioSet* A = FamilyToSet(data->Family1);
    TaioSet* B = FamilyToSet(data->Family2);
    double result = 0.0;
    int common = 0, different = 0; 

    for(int i_a = 0; i_a < A->Count; i_a++) {
        for(int i_b = 0; i_b < B->Count; i_b++) {
            int a = A->Numbers[i_a], b = B->Numbers[i_b];
            int com_1 = 0, diff_1 = 0;
            com_1 = a&b;
            diff_1 = a^b;

            common += CountOnes(com_1);
            different += CountOnes(diff_1);
        }
    }

    free(A->Numbers);
    free(A);
    free(B->Numbers);
    free(B);

    if(common == 0) return 1;
    if(different == 0) return 0;
    return 1 - (different*1.0 / common*1.0) / (common + different)*1.0;
}

int CountOnes(int N) {
    int count = 0;
 
    while (N > 0) {
        if (N & 1) {
            count++;
        }

        N = N >> 1;
    }
 
    return count;
}
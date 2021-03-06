#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <cstring>

#include <iostream>
#include <random>
#include <limits>
#include "sys/types.h"
#include "sys/sysinfo.h"

using namespace std;

struct sysinfo memInfo;
clock_t tStart;

#define VECTOR long long
#define MAX_LEN 24
#define HALF_LEN (MAX_LEN/2)
#define MAX_VECTOR_COUNT (1 << MAX_LEN)


// Random engine

random_device rd;
mt19937_64 eng(rd());
uniform_int_distribution<VECTOR> distr;

VECTOR llrand() {
    return distr(eng) % MAX_VECTOR_COUNT;
} 


VECTOR matrix[MAX_LEN];             

void print_vector(VECTOR v) {
    VECTOR t = v;
    for (int i = 0; i < MAX_LEN; ++i) {
        if (v % 2 == 0){
            printf(" 1 "); 
        } else {
            printf("-1 ");
        }
        v = v / 2;
    }
    printf("\n");
}

void print_matrix() {
    for (int i = 0; i < MAX_LEN; ++i) {
        print_vector(matrix[i]);
    }
} 

bool check(VECTOR a, VECTOR b) {
    VECTOR c = a ^ b;
    int oc = 0;
    while (c > 0) {
        oc += c & 1;
        c >>= 1;
    }

    return (oc == HALF_LEN);
} 

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getRAM(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void finish() {
    print_matrix();
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    printf("RAM used: %d KB\n", getRAM());
}


int main() {
    tStart = clock();
    srand(time(NULL));

    memset(matrix, 0, sizeof(VECTOR) * MAX_LEN);
    VECTOR *cur_v, *new_v;
    cur_v = (VECTOR *) malloc(sizeof(VECTOR) * MAX_VECTOR_COUNT/2);
    new_v = (VECTOR *) malloc(sizeof(VECTOR) * MAX_VECTOR_COUNT/4);


    int p = 0;

    for (int i = 0; i < MAX_VECTOR_COUNT; ++i) 
        if (check(matrix[0], i))// && check(matrix[1], i))
            cur_v[p++] = i;

    cout << "Step 0. Current Current size of vector's list - " << p << endl;

    for (int step = 1; step < MAX_LEN; ++step) {
        // choise random vector
        VECTOR v = cur_v[llrand() % p];
        matrix[step] = v;
        int new_p = 0;
        for (int i = 0; i < p; ++i){
            if (check(v, cur_v[i])) {
                new_v[new_p++] = cur_v[i];    
            }
        }
        if (step != MAX_LEN-1 && new_p < 1) {
            cout << "Fail on step " << step << endl;
            finish();
            return 0;
        }
        VECTOR *t = cur_v;
        cur_v = new_v;
        new_v = t;
        p = new_p;
        cout << "Step " << step << ". Current Current size of vector's list - " << p << endl;
    }

    finish();
    return 0;
}

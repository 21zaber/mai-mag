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
#define VECTOR_COUNTER long long
#define LENGTH_COUNTER int

#define MEM_STEP 100000

LENGTH_COUNTER MAX_LEN;
LENGTH_COUNTER HALF_LEN;
VECTOR_COUNTER MAX_VECTOR_COUNT, VC;

const VECTOR powers[56] = {
    1,
    2,
    4,
    8,
    16,
    32,
    64,
    128,
    256,
    512,
    1024,
    2048,
    4096,
    8192,
    16384,
    32768,
    65536,
    131072,
    262144,
    524288,
    1048576,
    2097152,
    4194304,
    8388608,
    16777216,
    33554432,
    67108864,
    134217728,
    268435456,
    536870912,
    1073741824,
    2147483648,
    4294967296,
    8589934592,
    17179869184,
    34359738368,
    68719476736,
    137438953472,
    274877906944,
    549755813888,
    1099511627776,
    2199023255552,
    4398046511104,
    8796093022208,
    17592186044416,
    35184372088832,
    70368744177664,
    140737488355328,
    281474976710656,
    562949953421312,
    1125899906842624,
    2251799813685248,
    4503599627370496,
    9007199254740992,
    18014398509481984,
    36028797018963968
};


// Random engine

random_device rd;
mt19937_64 eng(rd());
uniform_int_distribution<VECTOR> distr;

VECTOR llrand() {
    return distr(eng) % MAX_VECTOR_COUNT;
} 


VECTOR *matrix;             

void print_vector(VECTOR v) {
    VECTOR t = v;
    for (int i = 0; i < MAX_LEN; ++i) {
        if (t % 2 == 0){
            printf(" 1 "); 
        } else {
            printf("-1 ");
        }
        t /= 2;
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
    int oc = __builtin_popcountll(c);

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

  //printf("\n");
  //for (int i = 0; i < MAX_LEN; ++i) {
  //    printf("%d\n", matrix[i]);
  //}
  //printf("\n");
  //printf("\n");
}

VECTOR get_prefix(VECTOR_COUNTER i) {
    VECTOR v = 0;
    for (int j = 0; j < i; ++ j) {
        if (matrix[j] & powers[i]) {
            v += powers[j];
        }
    }

    return v;
}



int main() {
    cin >> MAX_LEN >> VC;
    HALF_LEN =  (MAX_LEN/2);
    MAX_VECTOR_COUNT = powers[MAX_LEN];

    srand(time(NULL));
    tStart = clock();

    //cout << "Memory allocation: ";

    matrix = (VECTOR *) malloc(sizeof(VECTOR) * MAX_LEN);

    if (!matrix) {
        //cout << "Failed.\n";
        return 255;
    }

    //cout << "Done.\n";

    LENGTH_COUNTER quater_len = MAX_LEN / 4;
    matrix[0] = 0;

    LENGTH_COUNTER step = 1, cur_part = 2;


    VECTOR_COUNTER half_vector_count = MAX_VECTOR_COUNT / 2;

    VECTOR pr;
    bool flag;

    for (; step < MAX_LEN; ++step) {
        pr = get_prefix(step);
        VECTOR_COUNTER i = 0;

        for (; i < VC; ++i) {
            VECTOR v;
            if (step < HALF_LEN) {
                v = llrand() % powers[MAX_LEN - step];
                v = v << step;
                v += pr;
            } else {
                v = llrand() % MAX_VECTOR_COUNT;
            }

            flag = 1;

            for (int j = 0; j < step; ++j) {
                flag &= check(matrix[j], v);
            }

            if (flag) {
                matrix[step] = v;
                break;
            }
        }
        cout << "Step " << step << " finished with " << i+1 << " random vectors.\n";
        if (!matrix[step]) {
            cout << "Fail on step " << step << "\n";
            finish();
            return 0;
            break;
        }
    }

    finish();
    return 1;
}

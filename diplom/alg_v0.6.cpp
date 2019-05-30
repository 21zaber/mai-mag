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
}


int main() {
    cin >> MAX_LEN >> VC;
    HALF_LEN =  (MAX_LEN/2);
    MAX_VECTOR_COUNT = powers[MAX_LEN];

    srand(time(NULL));
    tStart = clock();

    cout << "Memory allocation: ";

    VECTOR *cur_v, *new_v;
    matrix = (VECTOR *) malloc(sizeof(VECTOR) * MAX_LEN);
    cur_v = (VECTOR *) malloc(sizeof(VECTOR) * VC);
    new_v = (VECTOR *) malloc(sizeof(VECTOR) * VC);

    if (!cur_v || !new_v || !matrix) {
        cout << "Failed.\n";
        return 0;
    }

    cout << "Done.\n";

    VECTOR_COUNTER p = 0;   

    LENGTH_COUNTER quater_len = MAX_LEN / 4;
    matrix[0] = 0;
    matrix[1] = ((VECTOR_COUNTER)1 << (MAX_LEN / 2)) - 1;
    matrix[2] =  ((VECTOR_COUNTER)1 << (quater_len * 3)) - 1;
    matrix[2] -= ((VECTOR_COUNTER)1 << (quater_len * 2)) - 1; 
    matrix[2] += ((VECTOR_COUNTER)1 << (quater_len * 1)) - 1; 

    VECTOR_COUNTER half_vector_count = MAX_VECTOR_COUNT / 2;

    cout << "Generate vetor list of size " << VC << endl;

    for (VECTOR_COUNTER i = 0; p < VC && i < half_vector_count; ++i) {
        VECTOR v = llrand() % half_vector_count;
        if (check(matrix[0], v) && check(matrix[1], v) && check(matrix[2], v))
            cur_v[p++] = v;
    }

    cout << "Step 2. Current Current size of vector's list - " << p << endl;

    cout << MAX_VECTOR_COUNT / p << endl;

    for (LENGTH_COUNTER step = 3; step < MAX_LEN; ++step) {
        // choise random vector
        VECTOR v = cur_v[llrand() % p];
        matrix[step] = v;
        VECTOR_COUNTER new_p = 0;

        // calc new vectors
        for (VECTOR_COUNTER i = 0; i < p; ++i){
            if (check(v, cur_v[i])) {
                new_v[new_p++] = cur_v[i];    
            }
        }

        // fail check
        if (step != MAX_LEN-1 && new_p < 1) {
            cout << "\n\nFail on step " << step << "\n\n";
            finish();
            return 0;
        }

        // iteration finish
        VECTOR *t = cur_v;
        cur_v = new_v;
        new_v = t;
        p = new_p;

        if (p < 100) {
            cout << "Too low number of vectors in current list, generate more" << endl;
            for (VECTOR_COUNTER i = 0; p < 100 && i < VC; ++i) {
                VECTOR v = llrand() % half_vector_count;
                bool f = true;
                for (VECTOR_COUNTER j = 0; j <= step; ++j) {
                    if (!check(matrix[j], v)) {
                        f = false;
                        break;
                    }
                }
                if (f)
                    cur_v[p++] = v;
            }
        }

        cout << "Step " << step << ". Current Current size of vector's list - " << p << endl;
        cout << MAX_VECTOR_COUNT / p << endl;
    }

    cout << "\n\nSuccess\n\n";

    finish();
    return 0;
}

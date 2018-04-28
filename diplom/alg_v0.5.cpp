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
#include <omp.h>
#include <ctime>

using namespace std;

struct sysinfo memInfo;
unsigned long long tStart;

#define VECTOR long long
#define VECTOR_COUNTER long long
#define LENGTH_COUNTER int

#define MEM_STEP 10000
#define THR_NUM 4

LENGTH_COUNTER MAX_LEN;
LENGTH_COUNTER HALF_LEN;
VECTOR_COUNTER MAX_VECTOR_COUNT;

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
    printf("Time taken: %.2fs\n", (double)(time(0) - tStart));

    printf("RAM used: %d KB\n", getRAM());
}


int main() {
    cin >> MAX_LEN;
    HALF_LEN =  (MAX_LEN/2);
    MAX_VECTOR_COUNT = (VECTOR)1 << MAX_LEN;//powers[MAX_LEN];

    srand(time(NULL));
    tStart = time(0);

    matrix = (VECTOR *) malloc(sizeof(VECTOR) * MAX_LEN);

    omp_lock_t lock;
    omp_init_lock(&lock);

    LENGTH_COUNTER quater_len = MAX_LEN / 4;
    matrix[0] = 0;
    matrix[1] = ((VECTOR_COUNTER)1 << (MAX_LEN / 2)) - 1;
    matrix[2] =  ((VECTOR_COUNTER)1 << (quater_len * 3)) - 1;
    matrix[2] -= ((VECTOR_COUNTER)1 << (quater_len * 2)) - 1; 
    matrix[2] += ((VECTOR_COUNTER)1 << (quater_len * 1)) - 1; 

    VECTOR_COUNTER half_vector_count = MAX_VECTOR_COUNT / 2;


    VECTOR *buf[THR_NUM];
    VECTOR_COUNTER p[THR_NUM];

    #pragma omp parallel num_threads(THR_NUM)
    {
        int tid = omp_get_thread_num();

        VECTOR_COUNTER cur_l = MEM_STEP;
        buf[tid] = (VECTOR *)malloc(sizeof(VECTOR) * cur_l);
        p[tid] = 0;

        #pragma omp for schedule(dynamic)
        for (VECTOR_COUNTER i = 0; i < half_vector_count; ++i) { 
            if (check(matrix[0], i) && check(matrix[1], i) && check(matrix[2], i))
                buf[tid][p[tid]++] = i;
            if (p[tid] >= cur_l) {
                cur_l += MEM_STEP;
                buf[tid] = (VECTOR *) realloc(buf[tid], sizeof(VECTOR) * cur_l);
            }
        }
    }

    // merge
    VECTOR_COUNTER cur_l = 0, mx_l = 0;
    for (int tid = 0; tid < THR_NUM; ++tid) {
        cur_l += p[tid];
        if (p[tid] > mx_l) mx_l = p[tid];
    }

    VECTOR *cur_v = (VECTOR *) malloc(sizeof(VECTOR) * cur_l);
    VECTOR_COUNTER tmp = 0;
    for (int tid = 0; tid < THR_NUM; ++tid) {
        for (int i = 0; i < p[tid]; ++i) {
            cur_v[tmp++] = buf[tid][i];
        }
    }

    // allign buffers
    for (int tid = 0; tid < THR_NUM; ++tid) {
        buf[tid] = (VECTOR *) realloc(buf[tid], sizeof(VECTOR) * mx_l);
    }

    cout << "Step 2. Current Current size of vector's list - " << cur_l << endl;

    for (LENGTH_COUNTER step = 3; step < MAX_LEN; ++step) {
        // choise random vector
        VECTOR v = cur_v[llrand() % cur_l];
        matrix[step] = v;

        // calc new vectors
        #pragma omp parallel num_threads(4)
        {
            int tid = omp_get_thread_num();
            p[tid] = 0;

            #pragma omp for schedule(dynamic)
            for (VECTOR_COUNTER i = 0; i < cur_l; ++i){
                if (check(v, cur_v[i])) {
                    buf[tid][p[tid]++] = cur_v[i];    
                }
            }
        }
        // merge
        cur_l = 0;
        for (int tid = 0; tid < THR_NUM; ++tid) {
            cur_l += p[tid];
        }

        VECTOR_COUNTER tmp = 0;
        for (int tid = 0; tid < THR_NUM; ++tid) {
            for (int i = 0; i < p[tid]; ++i) {
                cur_v[tmp++] = buf[tid][i];
            }
        }

        // fail check
        if (step != MAX_LEN-1 && cur_l < 1) {
            cout << "\n\nFail on step " << step << "\n\n";
            finish();
            return 0;
        }

        // iteration finish
        cout << "Step " << step << ". Current Current size of vector's list - " << cur_l << endl;
    }

    cout << "\n\nSuccess\n\n";

    finish();
    return 0;
}

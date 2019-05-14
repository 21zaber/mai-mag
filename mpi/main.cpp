#include <bits/stdc++.h>

#define MX 34
#define MY 34
#define NITER 884
#define STEPITER 100

#define DEBUG 0

int main(int argc, char **argv) {
    int i, j, n, m;
    FILE *fp;

    float **fold;
    float **fnew;
    float **ptmp;

    printf("Solving heat conduction task on %d by %d grid\n", MX, MY);
    fflush(stdout);

    fold = (float**)calloc(MX, sizeof(float*));
    fnew = (float**)calloc(MX, sizeof(float*));

    if (!fold || !fnew) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    for (i = 0; i < MX; ++i) {
        fold[i] = (float*)calloc(MY, sizeof(float));
        fnew[i] = (float*)calloc(MY, sizeof(float));
        if (!fold[i] || !fnew[i]) {
            printf("Memory allocation failed!\n");
            return -1;
        }
        for (j = 0; j < MY; j++) {
            fold[i][j] = fnew[i][j] = 0.0;
            if ((i == 0) || (j == 0)) {
                fold[i][j] = fnew[i][j] = 1.0;
            } else if ((i == MX-1) || (j == MY-1)) { 
                fold[i][j] = fnew[i][j] = 0.5;
            }
        }
    }



    double start = time(NULL);

    for (n = 0; n < NITER; n++) {
      //if (!(n % STEPITER)) 
      //    printf("Iteration %d\n", n);

        for (i = 1; i < MX-1; i++) {
            for (j = 1; j < MY-1; j++) {
                fnew[i][j] = (fold[i][j+1] + fold[i][j-1] + fold[i-1][j] + fold[i+1][j]) * 0.25;
            }
        }

        ptmp = fold;
        fold = fnew;
        fnew = ptmp;
    }
    
    printf("calculation finished for: %lf\n", time(NULL) - start);

    fp = fopen("output", "w");
    for (i = 0; i < MX; i++) {
        fwrite(&(fold[i][0]), MY, sizeof(fold[0][0]), fp);
        if (DEBUG) {
            for (j = 0; j < MY; ++j) {
                printf("%f ", fold[i][j]);
            }
            printf("\n");
        }
    }

    fclose(fp);
    return 0;
}

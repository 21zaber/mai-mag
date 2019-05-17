#include <bits/stdc++.h>
#include <mpi.h>

//#define MX 514
//#define MY 1026
#define MX 258
#define MY 258
#define NITER 1000
#define STEPITER 100

#define DEBUG 0



int main(int argc, char **argv) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    double start = MPI_Wtime();
        
    if (!rank) printf("Size: %d\n", size);

    if ((MX-2) % size != 0) {
        if (!rank) printf("Bad size: %d\n", size);

        MPI_Finalize();
        return -1;
    }

    if (!rank) printf("Solving heat conduction task on %d by %d grid\n", MX, MY);
    if (!rank) fflush(stdout);

    int rs = (MX-2) / size + 2;
    int buf_size = 2 * MY * rs;
    int rbuf_size = buf_size * sizeof(float);
    float **fold, **fnew, **ptmp = NULL;
    fold = (float**)calloc(rs, sizeof(float*));
    fnew = (float**)calloc(rs, sizeof(float*));
    void *buf = calloc(buf_size, sizeof(float));

    if (!fold || !fnew || !buf) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    for (int i = 0; i < rs; ++i) {
        fold[i] = (float*)calloc(MY, sizeof(float));
        fnew[i] = (float*)calloc(MY, sizeof(float));
        if (!fold[i] || !fnew[i]) {
            printf("Memory allocation failed!\n");
            return -1;
        }
        for (int j = 0; j < MY; ++j) {
            fold[i][j] = fnew[i][j] = 0.0;
            if ((i+rank == 0) || (j == 0)) {
                fold[i][j] = fnew[i][j] = 1.0;
            } else if (((i == rs-1) && (rank == size-1)) || (j == MY-1)) { 
                fold[i][j] = fnew[i][j] = 0.5;
            }
        }
    }
    if (!rank) {
        printf("allocation+initialization finished for: %lf\n", MPI_Wtime() - start);
    }

    MPI_Buffer_attach(buf, rbuf_size);
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    for (int n = 0; n < NITER; ++n) {
      //if (!(n % STEPITER) && !rank) 
      //    printf("Iteration %d\n", n);

        for (int i = 1; i < rs-1; ++i) {
            for (int j = 1; j < MY-1; ++j) {
                fnew[i][j] = (fold[i][j+1] + fold[i][j-1] + fold[i-1][j] + fold[i+1][j]) * 0.25;
            }
        }

        MPI_Buffer_detach(&buf, &rbuf_size);
        MPI_Buffer_attach(buf, rbuf_size);

        ptmp = fold;
        fold = fnew;
        fnew = ptmp;

        if (rank) {
            MPI_Bsend(fold[1], MY, MPI_FLOAT, rank-1, 1, MPI_COMM_WORLD);
        }
        if (rank < size-1) {
            MPI_Bsend(fold[rs-2], MY, MPI_FLOAT, rank+1, 2, MPI_COMM_WORLD);
        }
        if (rank) {
            MPI_Recv(fold[0], MY, MPI_FLOAT, rank-1, 2, MPI_COMM_WORLD, &status);
        }
        if (rank < size-1) {
            MPI_Recv(fold[rs-1], MY, MPI_FLOAT, rank+1, 1, MPI_COMM_WORLD, &status);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    FILE *fp;
    if (!rank) {
        printf("calculation finished for: %lf\n", MPI_Wtime() - start);
    }
  //if (!rank)
  //for (int i = 0; i < rs; ++i) {
  //    for (int j = 0; j < MY; ++j) {
  //        printf("%f ", fold[i][j]);
  //    }
  //    printf("\n");
  //}

    MPI_Buffer_detach(&buf, &rbuf_size);
    MPI_Buffer_attach(buf, rbuf_size);
    if (!rank) {
        for (int i = 0; i < rs-1; ++i) {
            for (int j = 0; j < MY; ++j) {
                printf("%f ", fold[i][j]);
            }
            printf("\n");
        } 

        MPI_Bsend(fold[0], 1, MPI_FLOAT, rank+1, 1, MPI_COMM_WORLD);
    } else {
        MPI_Recv(fold[0], 1, MPI_FLOAT, rank-1, 1, MPI_COMM_WORLD, &status);

        int c = rs-1;
        if (rank == size-1) ++c;

        for (int i = 1; i < c; ++i) { 
            for (int j = 0; j < MY; ++j) {
                printf("%f ", fold[i][j]);
            }
            printf("\n");
        } 

        if (rank < size-1)
            MPI_Bsend(fold[0], 1, MPI_FLOAT, rank+1, 1, MPI_COMM_WORLD);
    }

    MPI_Buffer_detach(&buf, &rbuf_size);
    MPI_Finalize();
    return 0;
}

#include <bits/stdc++.h>
#include <mpi.h>

#define MX 66
#define MY 66
//#define MX 4098
//#define MY 4098
#define NITER 10000
#define STEPITER 100

#define DEBUG 0

#define ERR 0.0001

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
    int buf_size = 2 * MY * rs + 100;
    int rbuf_size = buf_size * sizeof(float);
    float **fold, **fnew, **ptmp = NULL;
    fold = (float**)calloc(rs, sizeof(float*));
    fnew = (float**)calloc(rs, sizeof(float*));
    void *buf = calloc(buf_size, sizeof(float));

    int *send_sz, *send_sh, *recv_sz, *recv_sh;
    send_sz = (int*)calloc(size, sizeof(int));
    send_sh = (int*)calloc(size, sizeof(int));
    recv_sz = (int*)calloc(size, sizeof(int));
    recv_sh = (int*)calloc(size, sizeof(int));

    memset(send_sz, 0, size * sizeof(int));
    memset(send_sh, 0, size * sizeof(int));
    memset(recv_sz, 0, size * sizeof(int));
    memset(recv_sh, 0, size * sizeof(int));

    if (rank > 0) {
        send_sz[rank - 1] = MY;
        send_sh[rank - 1] = MY;
        recv_sz[rank - 1] = MY;
        recv_sh[rank - 1] = 0;
    }
    if (rank < size - 1) {
        send_sz[rank + 1] = MY;
        send_sh[rank + 1] = MY * (rs-2);
        recv_sz[rank + 1] = MY;
        recv_sh[rank + 1] = MY * (rs-1);
    }

    if (!fold || !fnew || !buf) {
        printf("Memory allocation failed!\n");fflush(stdout);
        return -1;
    }

    float *dold = (float*)calloc(MY*rs, sizeof(float));
    float *dnew = (float*)calloc(MY*rs, sizeof(float));
    

    for (int i = 0; i < rs; ++i) {
        fold[i] = &dold[i*MY];
        fnew[i] = &dnew[i*MY];
        if (!fold[i] || !fnew[i]) {
            printf("Memory allocation failed!\n");fflush(stdout);
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

    float err = 1.0, lerr = 1.0;
    int n;

    for (n = 0; n < NITER; ++n) {
      //if (!(n % STEPITER) && !rank) 
      //    printf("Iteration %d\n", n);
      
        lerr = 0;

        for (int i = 1; i < rs-1; ++i) {
            for (int j = 1; j < MY-1; ++j) {
                fnew[i][j] = (fold[i][j+1] + fold[i][j-1] + fold[i-1][j] + fold[i+1][j]) * 0.25;
                lerr = std::max(lerr, (float)fabs(fnew[i][j]-fold[i][j]));
            }
        }

        MPI_Buffer_detach(&buf, &rbuf_size);
        MPI_Buffer_attach(buf, rbuf_size);

        ptmp = fold;
        fold = fnew;
        fnew = ptmp;
        float *t = dold;
        dold = dnew;
        dnew = t;

        MPI_Alltoallv(dold, send_sz, send_sh, MPI_FLOAT, dold, recv_sz, recv_sh, MPI_FLOAT, MPI_COMM_WORLD);
        MPI_Allreduce(&lerr, &err, 1, MPI_FLOAT, MPI_MAX, MPI_COMM_WORLD);

        if (err < ERR) {
            if (!rank) printf("precision achieved %f\n", err);
            break;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    FILE *fp;
    if (!rank) {
        printf("calculation finished for: %lf with %d iterations\n", MPI_Wtime() - start, n);
        fp = fopen("output", "w");
        fclose(fp); 
    }

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

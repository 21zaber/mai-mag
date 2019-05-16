#include <bits/stdc++.h>
#include <mpi.h>

#define STEPITER 100
#define DEBUG 0

int main(int argc, char **argv) {
    int size, rank;
    int MX = 34, MY = 34, NITER = 100;
    float ERR = 0.0001;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    double start_ts = MPI_Wtime();

    if (argc != 6) {
        if (!rank) printf("Wrong params");
        return -1;
    }

    MX = std::atoi(argv[1]);
    MY = std::atoi(argv[2]);
    NITER = std::atoi(argv[3]);
    ERR = std::stof(argv[4]);
    char *fname = argv[5];

    if (!rank) printf("Size: %d task: %dx%d\n", size, MX, MY);

    int rs, *len, *offset, bsize; 
    float *value; 
    void *buf = NULL;

    if (!rank) {
        std::ifstream inp;
        inp.open(fname);

        int s = 0;
        std::vector<int> os, ls, ps; // offsets, lens, prefixsums
        std::vector<float> v;       // defaule values

        ps.push_back(0);

        for (int i = 0; i < MX; ++i) {
            int a, o;
            float b;

            inp >> o >> a >> b;
            os.push_back(o);
            ls.push_back(a);
            v.push_back(b);
            ps.push_back(s+=a);
        }

        int ac = s / size, l = 0;
        int mxl = 0; // max number of strings in proc
        std::vector<int> rss, start; // number of strings, shitf of first string

        printf("Total cells: %d, average cels per proc: %d\n", s, ac);

        for (int i = 1; i < MX && rss.size() < size-1; ++i) {
            if (ps[i] - ps[l] >= ac) {
                rss.push_back(i-l);
                mxl = std::max(mxl, i-l);
                start.push_back(l);
                l = i;
            }
        }
        rss.push_back(MX-l-1);
        mxl = std::max(mxl, MX-l-1) + 5;
        start.push_back(l);


        len = (int*)calloc(mxl, sizeof(int));
        offset = (int*)calloc(mxl, sizeof(int)); 
        value = (float*)calloc(mxl, sizeof(float)); 

        bsize = 5 * size * mxl * std::max(sizeof(int), sizeof(float));
        buf = malloc(bsize);
        MPI_Buffer_attach(buf, bsize);
        
        // send offsets, lens and values to other procs
        for (int i = 1; i < size; ++i) {
            rs = rss[i] + 2;
            MPI_Bsend(&rs, 1, MPI_INT, i, 1, MPI_COMM_WORLD);    
            for (int j = -1; j <= rss[i]; ++j) {
                len[j+1] = ls[start[i]+j];
                offset[j+1] = os[start[i]+j];
                value[j+1] = v[start[i]+j];
            } 
            MPI_Bsend(len, rs, MPI_INT, i, 2, MPI_COMM_WORLD);    
            MPI_Bsend(offset, rs, MPI_INT, i, 3, MPI_COMM_WORLD);    
            MPI_Bsend(value, rs, MPI_FLOAT, i, 4, MPI_COMM_WORLD);    
        }
        rs = rss[0] + 1;
        for (int j = 0; j <= rss[0]; ++j) {
            len[j] = ls[start[0]+j];
            offset[j] = os[start[0]+j];
            value[j] = v[start[0]+j];
        } 
    } else {
        MPI_Recv(&rs, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        len = (int*)calloc(rs, sizeof(int));
        offset = (int*)calloc(rs, sizeof(int)); 
        value = (float*)calloc(rs, sizeof(float)); 

        MPI_Recv(len, rs, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);
        MPI_Recv(offset, rs, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
        MPI_Recv(value, rs, MPI_FLOAT, 0, 4, MPI_COMM_WORLD, &status);
    }

    int sm = 0;

    for (int i = 0; i < size; ++i){
        if (rank == i) {
            printf("Proc #%d, total strings: %d, ", rank, rs);
            sm  = 0;
            for (int j = 0; j < rs; ++j) { sm += len[j]; }
            printf("total cells: %d\n", sm);
          //for (int j = 0; j < rs; ++j) {
          //    printf("\t%d %d %f\n", len[j], offset[j], value[j]);
          //}
          //printf("\n");
        }
        fflush(stdout);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (buf) {
        MPI_Buffer_detach(&buf, &bsize);
        free(buf);
    }

    float *dold = (float*)calloc(sm, sizeof(float));
    float *dnew = (float*)calloc(sm, sizeof(float));
    float **pold = (float**)calloc(rs, sizeof(float*)); 
    float **pnew = (float**)calloc(rs, sizeof(float*));

    for (int i = 0, q = 0; i < rs; ++i) {
        pold[i] = &dold[q];
        pnew[i] = &dnew[q];

        q += len[i];

        pold[i][0] = value[i];
        pold[i][len[i]-1] = value[i];
        pnew[i][0] = value[i];
        pnew[i][len[i]-1] = value[i];
    }

    if (!rank) {
        for (int i = 0; i < len[0]; dold[i++] = value[0]);
        for (int i = 0; i < len[0]; dnew[i++] = value[0]);
    }
    if (rank == size-1) {
        for (int i = 0; i < len[rs-1]; pold[rs-1][i++] = value[rs-1]);
        for (int i = 0; i < len[rs-1]; pnew[rs-1][i++] = value[rs-1]);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    fflush(stdout);
    MPI_Barrier(MPI_COMM_WORLD);

    // test output all table without offsets
  //for (int i = 0; i < size; ++i){
  //    if (rank == i) {
  //        int st = 1, fn = rs-1;
  //        if (!rank) st = 0;
  //        if (rank == size-1) fn++;
  //
  //        for (int j = st; j < fn; ++j) {
  //            for (int k = 0; k < len[j]; ++k){
  //                printf("%f ", pold[j][k]);
  //            }
  //            printf("\n");
  //        }
  //        fflush(stdout);
  //    }
  //    MPI_Barrier(MPI_COMM_WORLD);
  //}
    
    MPI_Barrier(MPI_COMM_WORLD);
  
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
        send_sz[rank-1] = len[1];
        send_sh[rank-1] = len[0];
        //printf("send from %d to %d, len %d\n", rank, rank-1, len[1]);
        recv_sz[rank-1] = len[0];
        recv_sh[rank-1] = 0;
        //printf("recv who %d from %d, len %d\n", rank, rank-1, len[0]);
    }
    if (rank < size - 1) {
        send_sz[rank+1] = len[rs-2];
        send_sh[rank+1] = sm - len[rs-1] - len[rs-2];
        //printf("send from %d to %d, len %d\n", rank, rank+1, len[rs-2]);
        recv_sz[rank+1] = len[rs-1];
        recv_sh[rank+1] = sm - len[rs-1];
        //printf("recv who %d from %d, len %d\n", rank, rank+1, len[rs-1]);
    }

    int rbuf_size = 2 * MY;
    buf = malloc(rbuf_size);

    if (!rank) {
        printf("allocation+initialization finished for: %lf\n", MPI_Wtime() - start_ts);
    }

    MPI_Buffer_attach(buf, rbuf_size);
    MPI_Barrier(MPI_COMM_WORLD);
    start_ts = MPI_Wtime();

    float err = 1.0, lerr = 1.0;
    int n;

    for (n = 0; n < NITER; ++n) {
      //if (!(n % STEPITER) && !rank) 
      //    printf("Iteration %d\n", n);
      
        lerr = 0;

        for (int i = 1; i < rs-1; ++i) {
            for (int j = 1; j < len[i]-1; ++j) {
                pnew[i][j] = pold[i][j-1] + pold[i][j+1];

              //if (j) {
              //    pnew[i][j] += pold[i][j-1];
              //}
              //if (j < len[i]-1) {
              //    pnew[i][j] += pold[i][j+1];
              //}
                int t = j+offset[i]-offset[i-1];
                if (t >= 0 && t < len[i-1]) {
                    pnew[i][j] += pold[i-1][t];
                }
                t = j+offset[i]-offset[i+1];
                if (t >= 0 && t < len[i+1]) {
                    pnew[i][j] += pold[i+1][t];
                }

                pnew[i][j] *= 0.25;
                lerr = std::max(lerr, (float)fabs(pnew[i][j]-pold[i][j]));
            }
        }

        MPI_Buffer_detach(&buf, &rbuf_size);
        MPI_Buffer_attach(buf, rbuf_size);

        float **ptmp = pold;
        pold = pnew;
        pnew = ptmp;
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
        printf("calculation finished for: %lf with %d iterations, end precision %f\n", MPI_Wtime() - start_ts, n, err);
        fp = fopen("/home/n.zabarin/mpi/cp/output", "w");
        fclose(fp); 
        fp = fopen("/home/n.zabarin/mpi/cp/routput", "w");
        fclose(fp); 
    }

    MPI_Buffer_detach(&buf, &rbuf_size);
    MPI_Buffer_attach(buf, rbuf_size);
    if (!rank) {
        fp = fopen("/home/n.zabarin/mpi/cp/output", "ab");
        for (int i = 0; i < rs-1; ++i) 
            fwrite(&(pold[i][0]), len[i], sizeof(float), fp);
        fclose(fp);   

        if (size > 1) {
            MPI_Bsend(pnew[0], 1, MPI_FLOAT, rank+1, 1, MPI_COMM_WORLD);
        } else {
            fp = fopen("/home/n.zabarin/mpi/cp/output", "ab");
            fwrite(&(pold[rs-1][0]), len[rs-1], sizeof(float), fp);
            fclose(fp);   
        }
    } else {
        MPI_Recv(pnew[0], 1, MPI_FLOAT, rank-1, 1, MPI_COMM_WORLD, &status);
        fp = fopen("/home/n.zabarin/mpi/cp/output", "ab");

        int c = rs-1;
        if (rank == size-1) c++;

        for (int i = 1; i < c; ++i) 
            fwrite(&(pold[i][0]), len[i], sizeof(float), fp);
        fclose(fp);

        if (rank < size-1)
            MPI_Bsend(pnew[0], 1, MPI_FLOAT, rank+1, 1, MPI_COMM_WORLD);
    }

    MPI_Buffer_detach(&buf, &rbuf_size);


    for (int i = 0; i < size; ++i){
        if (rank == i) {
            int st = 1, fn = rs-1;
            if (!rank) st = 0;
            if (rank == size-1) fn++;

            fp = fopen("/home/n.zabarin/mpi/cp/routput", "a");
    
            for (int j = st; j < fn; ++j) {
                for (int k = 0; k < offset[j]; ++k) 
                    fprintf(fp, "0.0 ");
                for (int k = 0; k < len[j]; ++k){
                    fprintf(fp, "%f ", pold[j][k]);
                }
                fprintf(fp, "\n");
            }
            fclose(fp);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;   
}

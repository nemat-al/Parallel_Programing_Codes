#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"
int main(int argc, char* argv[])
{
    double* x, * y, * local_x, * local_y;
    int n = 1000000;        //length of each vector
    x = (double*)calloc(n, sizeof(double)); // first vector
    y = (double*)calloc(n, sizeof(double)); // second vector
    int    local_n;  
    double  product, local_product;
    int    size, rank, i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // In the zero thread, intializing both vectors
    if (rank == 0) {

        for (i = 0; i < n; i++) { x[i] = 1.0;  y[i] = 1.0; }
    }
    // Intializing local vectors for each thread
    local_n = n / size;
    local_x = (double*)calloc(local_n, sizeof(double));
    local_y = (double*)calloc(local_n, sizeof(double));
    // send the vectors equal parts to all threads
    MPI_Scatter(x, local_n, MPI_DOUBLE, local_x, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, local_n, MPI_DOUBLE, local_y, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // Calculating of local product
    local_product = 0.0;
    for (i = 0; i < local_n; i++)
        local_product += local_x[i] * local_y[i];
    free(local_x); free(local_y);
    // Calculating of total product
    MPI_Reduce(&local_product, &product, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    // printing the final dot product
    if (rank == 0) {
        printf("The product product is %f\n", product);
    }  
    MPI_Finalize();
    return 0;
}
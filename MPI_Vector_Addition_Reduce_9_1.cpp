#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int array_len = 1000000;
	double start_time;
	int local_sum , total_sum;
	int* locals_sum = new int[size]();
	int local_len = array_len / size;
	// Initialising array and local array
	int* array = new int[array_len]();
	int* local_Array = new int[local_len]();
	// Generating the array in the root processor
	if (rank == 0)
	{
		for (int i = 0; i < 1000000; i++)
			array[i] = 1;
	}
	//////////////////////////Method 2 (Reduce)///////////////////////////////
		// Splitting the array among the processers
		// Starting time in process 0
	if (rank == 0) start_time = MPI_Wtime();
	MPI_Scatter(array, local_len, MPI_INT, local_Array, local_len, MPI_INT, 0, MPI_COMM_WORLD);
	// calculating the local sum in each processor
	local_sum = 0, total_sum = 0;
	for (int i = 0; i < local_len; i++) local_sum += local_Array[i];
	// Summing all the local_sums in the root processor
	MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	// Calculating the execution time and pronting it
	if (rank == 0)
	{
		printf("Total Sum: %d\n", total_sum);
		printf("Reduce Execution time %f\n", (MPI_Wtime() - start_time));
	}

	MPI_Finalize();
	return 0;
}
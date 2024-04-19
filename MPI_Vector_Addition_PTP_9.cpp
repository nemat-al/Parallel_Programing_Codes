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
	int local_sum ;
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
	///////////////////////////Method 1 (Point to Point)//////////////////////////////
	// Starting time in process 0
	if (rank == 0) start_time = MPI_Wtime();
	// Splitting the array among the processers
	MPI_Scatter(array, local_len, MPI_INT, local_Array, local_len, MPI_INT, 0, MPI_COMM_WORLD);
	// calculating the local sum in each processor
	local_sum = 0; 
	for (int i = 0; i < (local_len); i++) local_sum += local_Array[i];
	//Gathering the local sums in a cascade way
	for (int level = 2; level <= size; level *= 2)
	{
		// Threads that will receive the parts of the sum
		if (rank % level == 0)
		{
				int temp;
				MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				local_sum += temp;
				cout << "Level: " << level << "  Receiver thread: " << rank << "  Sender thread:  " << status.MPI_SOURCE << "  value:  "<< temp << "  Accumulated total:  " << local_sum<<endl;
		}
		// Threads that will send their parts of the sum
		else
		{
			MPI_Send(&local_sum, 1, MPI_INT, rank - (rank % level), 0, MPI_COMM_WORLD);
			break;
		}
	} 
	// Thread with 0 rank will print the final results
	if (rank == 0)
	{
		printf("Total answer: %d\n", local_sum);
		printf("Point to point execution time: %f \n", (MPI_Wtime() - start_time) );
	}
	MPI_Finalize();
	return 0;
}
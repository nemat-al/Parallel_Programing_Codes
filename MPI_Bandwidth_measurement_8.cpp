#include <iostream>
#include <stdexcept>
#include "mpi.h"
using namespace std;
int main(int argc, char** argv)
{
	int rank, n;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double start_time, finish_time, time;
	MPI_Status status;
    // The number of required to acheive the goal of the task is 2, otherwise raise an exception
	if (n != 2)
	{
		throw invalid_argument("For this task only two processers are required");
	}
    ////////// Calculating the bandwidth ////////////////
    // for loop with length 1,000,000 for changing the length of the message
	for (int len = 1; len <= 1000000; len *= 10)
	{
        // creating the message with the (len) length
		int* message = (int*)malloc(len * sizeof(int));
		if (rank == 0) // timing is held by process 0
		{
			start_time = MPI_Wtime();
		}
		for (int i = 0; i < 10; i++)
		{
			if (rank == 0) // process 0 sends and receives messages to/from process 1
			{
				MPI_Send(message, len, MPI_INT, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(message, len, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

			}
			else if (rank == 1) // process 1 sends and receives messages to/from process 0
			{
				MPI_Recv(message, len, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
				MPI_Send(message, len, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
		}
		if (rank == 0) // for each message length, process 0 prints the message length and the bandwidth
		{
			finish_time = MPI_Wtime();
			time = finish_time - start_time;
			double num_butes = len * sizeof(int);
			double num_Mbutes = num_butes / 1024 / 1024;
			double bandwidth = 2 * num_Mbutes * n / time;
			cout << "Message length  " << len<< "  Bandwidth MB/s  " << bandwidth<<endl;
		}
		free(message);
	}
    ////////// Calculating the latency ////////////////
	int signal_message = 1;
		if (rank == 0)  // timing is held by process 0
		{
			start_time = MPI_Wtime();
		}
        // repeating the exchange of messages 10 times
		for (int i = 1; i <= 10; i ++)
		{
			if (rank == 0)
			{
				MPI_Send(&signal_message, 0, MPI_INT, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(&signal_message, 0, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

			}
			else if (rank == 1)
			{
				MPI_Recv(&signal_message, 0, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
				MPI_Send(&signal_message, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
		}
		if (rank == 0) // process 0 prints the Latency
		{
			time = MPI_Wtime() - start_time;
			double latency = time / (2 * n);
			cout << "Latency  " <<  latency << endl;

		}
	MPI_Finalize();
	return 0;
}
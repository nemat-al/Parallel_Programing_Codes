#include <stdio.h>
#include <string.h>
#include <iostream>
#include "mpi.h"
using namespace std;
#define BUFSIZE 100
// Adding function to create a file and write the content inside it.
void creat_file(const char* filename, const char* sentence, int len)
{
	MPI_File fh;
	MPI_Status status;
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	MPI_File_write(fh, sentence, len, MPI_CHAR, &status);
	MPI_File_close(&fh);
}
int main(int argc, char** argv)
{
	int bufsize, num, sum;
	MPI_Init(&argc, &argv);
	// creating and writing content in file
	creat_file("file.txt", "A file is created and filled with a sentence!", 45);
	MPI_Status status;
	MPI_File fh;
	char buf[BUFSIZE];
	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("%.45s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
	//print the number of read symbols sum from the file
	cout << "Number of Read Symbols" << sum <<endl;  
	//Deleting file on close 
	if (argc > 1 && strcmp(argv[1], "--delete") == 0)
		MPI_File_delete("file.txt", MPI_INFO_NULL);
	MPI_Finalize();
}


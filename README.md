## Parallel Programing Codes
Implementing Tasks in OpenMP/MPI C++.

The tasks are assignements for Parallel Programing Course at ITMO university.

#### 1.[Counting words in a line - OpenMp](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/OMP_Counting_words.cpp)
The program aims to count words in a line. Any sequence of characters without separators is considered a word. Separators are spaces, tabs, newlines.


#### 2.[Finding the maximum value of a vector - OpenMp](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/OMP_Max_Vector.cpp)
The main goal of the program is to find the maximum value of a vector. In order to achieve that, I use the OpenMP reduction clause.
The program also studies the dependence of the runtime on the number of threads used (from 1 to 10)
for a vector that contains 1,000,000 elements.


#### 3.[Matrix multiplication - OpenMp](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/OMP_Mat_Mult.cpp)
The program implements two dimension matrix multiplication with different loop orders.
For each loop order, the computation is done for one thread then for multiple threads
from 2 to 10. For each case the time of execution and the efficiency are measured. The
arrays are shared among threads, meanwhile the indices are private to prevent different
threads from editing them simultaneously.


#### 4.[Dot product of vectors - MPI](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Dot_product_vectors_7.cpp)
MPI program that implements the dot product of two vectors distributed
between processes. Two vectors with a size of at least 1,000,000 elements are
initialized at process zero and filled with “1”, then they are sent in equal parts to all
processes. Parts of vectors are scalar multiplied on each process, the result is sent to
the root process and summed up. The total is displayed


#### 5.[Bandwidth measurement - MPI](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Bandwidth_measurement_8.cpp)
MPI program in which two processes exchange messages, the time per exchange iteration is measured, and the dependence of the exchange time on the
message length is studied. 
The latency and maximum achievable bandwidth of the communication network are calculated.
The message length in bytes and the throughput in MB/s is displayed. 
The length of the message is changed in a loop starting from 1 element and increase to 1,000,000 elements, increasing by 10 times at each
iteration.


#### 6.MPI_Reduce - MPI
[MPI program](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Vector_Addition_PTP_9.cpp) in which the global vector addition operation is modeled by a doubling (cascade) scheme using point-to-point data transfers. 
[Another execution](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Vector_Addition_Reduce_9_1.cpp) is done using the MPI_Reduce procedure on as many processes as possible.

Each process stores an array of 1,000,000 elements equal to ‘1’

#### 7.[Combined reception and transmission of messages - MPI](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Ring_Topology_Exchange_11.cpp)
MPI program for ring topology exchange using the MPI_Sendrecv() function.

 
#### 8.[Delayed interactions. Scheme of an iterative method with exchange over a ring topology using pending requests - MPI](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Ring_Topology_12.cpp)
MPI allows for non-blocking operations to form whole packets of requests for
communication operations MPI_Send_init and MPI_Recv_init, which are started by the
MPI_Start or MPI_Startall functions. Checking for completion of execution is performed by
conventional means using the functions of the WAIT and TEST families.


#### 9.[Collective process interactions. Barrier - MPI](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Barrier_13.cpp)
Finding out which process will perform the multiplication of two 500x500 square matrices faster


#### 10.[Custom global operations. Custom global function - MPI](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Gobal_14.cpp)
In the program each thread initializes integer array. The array values are generated in a way
related to the threas’s rank number.
In order to gather all the arrays in the root thread, the function MPI_Reduce was used.
A function max_fun() was initialized to find the maximum value at each position of array.
In order to check the correctness of execution, the MPI_MAX operation in the MPI_Reduce()
function was used. 


#### 11.[Parallel I / O. Working with files. Access to data. Buffered reading from a file. - MPI](https://github.com/neematAllosh/Parallel_Programing_Codes/blob/master/MPI_Buffered_Read_File_20.cpp)
In order to implement the tasks, several functions were used:
MPI_File_open() to open a file.
MPI_File_write() to write the content in the file.
MPI_File_close() to close the opened file.
MPI_File_set_view() to select where to start typing inside the file.
MPI_File_delete() to delete a file.


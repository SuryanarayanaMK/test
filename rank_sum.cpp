#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<mpi.h>
#define Pi  3.141592653589793238
#define N 100000000
#include<ctime>

using namespace std;

int main(int argc,char **argv){

 int rank,size;
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 MPI_Status status;
 MPI_Request request;
 
 int count = 0;
 int root  = 0;
 int total_count = 0;
 int Np    = N/size;
 float tempx,tempy;
 float pi_value = M_PI;
 time_t t = time(0);
 float pi = 0;
 double sum = 0;
 int total_sum = 0;

 srand(t+rank);
 int *rbuf;
 rbuf = (int*)malloc(size*sizeof(int)); 

  double start = MPI_Wtime();
 
   sum = rank*rank;
   MPI_Allgather(&rank,1,MPI_INT,rbuf,1,MPI_INT,MPI_COMM_WORLD);
  
   for(int i=0;i<size;i++)
          total_sum = total_sum + rbuf[i];
  
  // MPI_Bcast(&total_sum,1,MPI_INT,root,MPI_COMM_WORLD);
          cout << "the sum is" << total_sum << " in rank " << endl;

   MPI_Finalize();
   return 0;

}

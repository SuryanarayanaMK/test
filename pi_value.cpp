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
 srand(t+rank);

  double start = MPI_Wtime();
  
  for(int i=0;i<Np;i++){
    
      tempx = (float)rand()/(float)RAND_MAX;
      tempy = (float)rand()/(float)RAND_MAX;
     
      if((tempx*tempx+ tempy*tempy)<=1.0)
        count = count + 1.;
  } 
 
//   MPI_Reduce(&count,&total_count,1,MPI_INT,MPI_SUM,root,MPI_COMM_WORLD);
     MPI_Allreduce(&count,&total_count,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

 //  if(rank==0){
    pi = 4.*total_count/(N);
    cout << " the value of pi in rank" << rank << " is " << pi << endl;
    cout << "error is " << Pi-pi << endl;
 //  }

  // MPI_Bcast(&pi,1,MPI_INT,root,MPI_COMM_WORLD);
 //  cout << "the value of pi in rank" << rank << " is " << pi << endl;
   
   double end = MPI_Wtime();   

   cout << " time taken is " << end - start << endl;
   MPI_Finalize();
  return 0;
}

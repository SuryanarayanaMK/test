#include<iostream>
#include<mpi.h>
using namespace std;

int main(int argc,char **argv){

 int error =  MPI_Init(&argc,&argv);
 int myrank,var,var1;
 int size;
 int ierror;
 MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
 MPI_Comm_size(MPI_COMM_WORLD,&size);
 MPI_Status status;
 MPI_Request request;
 int other = 1 - myrank;
 double start;

 int left  = (size + myrank - 1)%size;
 int right = (myrank + 1)%size;
 int sum = 0;
 int update_sum = 0;

 sum = myrank;

 for(int i=1;i<size;i++){

  //  MPI_Issend(&sum,1,MPI_INT,right,0,MPI_COMM_WORLD,&request);   
    MPI_Irecv(&update_sum,1,MPI_INT,left,0,MPI_COMM_WORLD,&request);
   // MPI_Recv(&update_sum,1,MPI_INT,left,0,MPI_COMM_WORLD,&status);
    MPI_Ssend(&sum,1,MPI_INT,right,0,MPI_COMM_WORLD);  
    MPI_Wait(&request,&status);
    sum = update_sum + myrank; 
 
 }

 if(myrank==0)
  cout << sum << endl;

 MPI_Finalize();
 return 0;

}

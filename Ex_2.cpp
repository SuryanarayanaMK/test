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
 int other = 1 - myrank;
 double start;

/*for(int i=0;i<10;i++){ 
 if(myrank==0){
  var = myrank;
  MPI_Ssend(&var,1,MPI_INT,1,0,MPI_COMM_WORLD);
  MPI_Recv(&var1,1,MPI_INT,1,1,MPI_COMM_WORLD,&status);
  cout << "In rank " << myrank << " other rank is " << var1 << endl;
 }

 if(myrank==1){
  var1 = myrank;
  MPI_Recv(&var,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
  MPI_Ssend(&var1,1,MPI_INT,0,1,MPI_COMM_WORLD);
  cout << "In rank " << myrank << " other rank is " << var << endl;
 }
}
*/

if(myrank==0)
 start = MPI_Wtime();

 for(int i=0;i<1000000;i++){
  MPI_Sendrecv(&myrank,1,MPI_INT,other,myrank,&var,1,MPI_INT,other,other,MPI_COMM_WORLD,&status);
//  cout << "my rank is " << myrank << "other rank is " << var << endl;
 }
 
 if(myrank==0)
   cout << " the time taken is " << MPI_Wtime() - start << endl;
 

 MPI_Finalize();
 return 0;

}

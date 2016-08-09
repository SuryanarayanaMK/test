#include<iostream>
#include<mpi.h>
using namespace std;

int main(int argc,char **argv){

 int error =  MPI_Init(&argc,&argv);
 int myrank;
 int size;
 int ierror;
 MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
 MPI_Comm_size(MPI_COMM_WORLD,&size);

/* 
 if(myrank==0)
    cout << "I am rank " << myrank << " and master of " << size << "tasks" << endl;
 else
    cout << "I am rank " << myrank << endl;
*/

 if(myrank%2!=0)
     cout << "I am rank " << myrank << endl;

 MPI_Finalize();
 return 0;

}

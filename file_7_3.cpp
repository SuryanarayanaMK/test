#include<iostream>
#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int main(int argc,char **argv){
 
  int rank,size;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Status status;
  MPI_Request request;

  MPI_File handle;

  MPI_File_open(MPI_COMM_WORLD,"rank.dat",MPI_MODE_RDWR|MPI_MODE_CREATE,MPI_INFO_NULL,&handle); // open/create the file
  
//  int size_MPI_INT;
//  MPI_TYPE_SIZE(MPI_INT,&size_MPI_INT);

//  MPI_File_preallocate(handle,)

  MPI_File_write_ordered(handle,&rank,1,MPI_INT,&status);

  MPI_File_close(&handle);  // closing the file
  
  MPI_File_open(MPI_COMM_WORLD,"rank.dat",MPI_MODE_RDONLY,MPI_INFO_NULL,&handle); // open/create the file
 
  MPI_Datatype sub_array;
  MPI_Datatype etype;
 
  int sub_size = 1;
  int ndim     = 1;
  int starts   = (size-1)-rank;   
  etype        = MPI_INT;

  MPI_Type_create_subarray(ndim,&size,&sub_size,&starts,MPI_ORDER_C,MPI_INT,&sub_array);
  MPI_Type_commit(&sub_array);

  int buffer;

  MPI_File_set_view(handle,0,etype,sub_array,"native",MPI_INFO_NULL); // sets the view of the file to the process
  MPI_File_read(handle,&buffer,1,etype,&status);
  
  cout << "rank  " << rank << " reads " << buffer << endl;

  MPI_File_close(&handle);  // closing the file
  
  MPI_Finalize();

 return 0;
}

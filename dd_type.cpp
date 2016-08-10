#include<iostream>
#include<mpi.h>

using namespace std;

struct dd_type{
   char tag;
  double x,y,z;  // if I change the order here,if I don't change the code below everything should remain the same
  int r,g,b; 
};

int main(int argc,char **argv){

  int rank,size;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Status status;
  MPI_Request request;
  int root = 0; 

  dd_type test;

  if(rank==0){
    test.r = 120;
    test.g = 120;
    test.b = 120;
    test.x = 0.3;
    test.y = 0.2;
    test.z = 0.1;
    test.tag = 'Q';
  }

  int blocks[3] = {1,3,3};

 // MPI_Datatype types[3] = {MPI_INT,MPI_DOUBLE,MPI_CHAR};
  MPI_Datatype types[3] = {MPI_CHAR,MPI_DOUBLE,MPI_INT};  // when I change the order here then
  MPI_Aint add_blck_0,add_blck_1,add_blck_2,add_blck_3;
  
  MPI_Get_address(&test,&add_blck_0);
  MPI_Get_address(&test.r,&add_blck_1);
  MPI_Get_address(&test.x,&add_blck_2);
  MPI_Get_address(&test.tag,&add_blck_3);
 
  MPI_Aint displacements[3]={(add_blck_3-add_blck_0),(add_blck_2-add_blck_0),(add_blck_1-add_blck_0)}; // I should change the order here
  MPI_Datatype derived_type;  
  MPI_Type_create_struct(3,blocks,displacements,types,&derived_type);
  MPI_Type_commit(&derived_type);

  MPI_Bcast(&test,1,derived_type,root,MPI_COMM_WORLD);

  if(rank==2){
      cout << int(test.r) << endl; 
      cout << int(test.g) << endl;
      cout << int(test.b) << endl;
      cout << test.x << endl;
      cout << test.y << endl;
      cout << test.z << endl;
      cout << test.tag << endl;
  }

  MPI_Type_free(&derived_type);
  MPI_Finalize();
 
  return 0;
}

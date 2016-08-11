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

  int nkeys;
   
  MPI_File_open(MPI_COMM_WORLD,"rank.dat",MPI_MODE_RDONLY,MPI_INFO_NULL,&handle); // open/create the file
 
  MPI_Info info_keys;  
  MPI_Info_create(&info_keys);

  MPI_File_get_info(handle,&info_keys);  // copy the file keys into info_keys
  MPI_Info_get_nkeys(info_keys,&nkeys);  // get the number of keys

  cout << " number of keys " << nkeys << endl;
 

  for(int i=0;i<nkeys;i++){
    char key[MPI_MAX_INFO_KEY];
    MPI_Info_get_nthkey(info_keys,i,key);  // 
    int valuelen,flag;
    MPI_Info_get_valuelen(info_keys,key,&valuelen,&flag); // length of the value of the key
    char value[valuelen+1];
    MPI_Info_get(info_keys,key,valuelen+1,value,&flag);   // value of the key
    cout << i << " key " << key << " value " << value << endl;   
  }

  MPI_Info_free(&info_keys);
  MPI_Finalize();
  return 0;
}
 

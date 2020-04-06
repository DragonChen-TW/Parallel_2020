/* This is a sample example for make news topology and subtopology */
#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
main(int argc, char *argv[])
{
  int a[10],b[10],npes,myrank,my2drank,new2drank,other_rank,other_coord;
  int i,dims[2],periods[2],my2dcoords[2],keep_dims[2];
  int coords[2];
  int shiftsource,shiftdest;
  MPI_Status status;
  MPI_Comm comm_2d,comm_col;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &npes);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  dims[0]=3;
  dims[1]=2;
  periods[0]=periods[1]=1;
  MPI_Cart_create(MPI_COMM_WORLD,2,dims,periods,1,&comm_2d);

  MPI_Comm_rank(comm_2d,&my2drank);
  MPI_Cart_coords(comm_2d,my2drank,2,my2dcoords);
  MPI_Cart_rank(comm_2d,my2dcoords,&new2drank);
  /* Here I assign value to the left processors, i.e. the
     processor with my2dcoords[1]=0 */
  if (my2dcoords[1]==0){
    if (my2dcoords[0]==0)
      a[0]=0;
    else if (my2dcoords[0]==1)
      a[0]=1;
    else if (my2dcoords[0]==2)
      a[0]=2;
  }

   MPI_Cart_shift(comm_2d,0,1,&shiftsource,&shiftdest);
  /* here is the subtopology, I turn off the 2nd coordinate,
     so the subtopology is in y-direction(or 1st coordinate
     direction */
  keep_dims[0]=1;
  keep_dims[1]=0;
  MPI_Cart_sub(comm_2d,keep_dims,&comm_col);
  coords[0]=my2dcoords[0];
  coords[1]=my2dcoords[1];
  /* We have actually 2-comm_col, but they share the same
     name, the following command just gives us the corresponding
     rank in each subtopology */
   MPI_Cart_rank(comm_col,&coords[0],&other_rank);
   printf("My rank %d , my 2drank %d my 2dcoord %d %d a= %d \n"
	,myrank,my2drank,my2dcoords[0],my2dcoords[1],a[0]);
	printf("\n");

   MPI_Bcast(a,1,MPI_INT,2,comm_col);
   /*printf("My rank %d , my 2drank %d my 2dcoord %d %d a= %d \n"
	,myrank,my2drank,my2dcoords[0],my2dcoords[1],a[0]);
	printf("\n");*/
	 printf("My rank %d , my 2drank %d new2d %d my 2dcoord %d %d  source %d dest %d\n",myrank,my2drank,new2drank,my2dcoords[0],my2dcoords[1],shiftsource,shiftdest);

  /*printf("My rank %d , my 2drank %d my 2dcoord %d %d other_rank %d   \n"
	 ,myrank,my2drank,my2dcoords[0],my2dcoords[1]
	 ,other_rank);*/
	 /*printf("My rank %d , my 2drank %d my 2dcoord %d %d a= %d \n"
	   ,myrank,my2drank,my2dcoords[0],my2dcoords[1],a[0]);*/
  MPI_Finalize();
}

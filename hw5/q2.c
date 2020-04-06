#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[]) {
	int npes, my_rank, my2drank, new2drank;
	int dims[2], periods[2], my2dcoords[2], keep_dims[2];
	MPI_Status status;
	MPI_Comm comm_2d, comm_col;

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	dims[0] = dims[1] = 4;
	periods[0] = periods[1] = 1;
	MPI_Cart_create(MPI_COMM_WORLD,2, dims, periods, 1, &comm_2d);

	MPI_Comm_rank(comm_2d,&my2drank);
	MPI_Cart_coords(comm_2d, my2drank, 2, my2dcoords);
	MPI_Cart_rank(comm_2d, my2dcoords, &new2drank);

	printf("My rank: %d, 2dcoord %d %d\n", my_rank, my2dcoords[0], my2dcoords[1]);

	// read file
	char f_name[128] = "lenna.pgm", mode[10];
	int lenx, leny, max_value, data[300][300];
	int i, j;
	FILE *fp;

	fp = fopen(f_name, "r");
	fscanf(fp, "%s", mode);
	fscanf(fp, "%d %d %d", &lenx, &leny, &max_value);
	if (my_rank == 0) {
		printf("%s\n", mode);
		printf("%d %d %d\n", lenx, leny, max_value);
	}
	for (i = 0; i < lenx; i++) {
		for (j = 0; j < leny; j++) {
			fscanf(fp, "%d", &data[i][j]);
		}
	}
	fclose(fp);

	// cut into files
	int block_len = lenx / 4;
	int start_i, start_j;
	start_i = my2dcoords[0] * block_len;
	start_j = my2dcoords[1] * block_len;
	printf("%d %d %d\n", my_rank, start_i, start_j);

	sprintf(f_name, "q2_out/lenna%d%d.pgm", my2dcoords[0], my2dcoords[1]);
	fp = fopen(f_name, "w");
	fprintf(fp, "%s\n%d %d\n%d\n", mode, block_len, block_len, max_value);

	for (i = start_i; i < start_i + block_len; i++) {
		for (j = start_j; j < start_j + block_len; j++) {
			fprintf(fp, "%d ", data[i][j]);
		}
		fprintf(fp, "\n");
	}

	MPI_Finalize();

	return 0;
}

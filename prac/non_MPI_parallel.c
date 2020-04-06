#include <stdio.h>
#include <mpi.h>

#define BUF_SIZE 10

int main(int argc, char const *argv[]) {
	int npes, my_rank;

	MPI_Init(&argc, (char***)&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int i;
	int buf[BUF_SIZE];
	char f_name[128];

	for (i = 0; i < BUF_SIZE; i++) {
		buf[i] = my_rank * BUF_SIZE + i;
	}

	FILE *fp;
	sprintf(f_name, "test_file.%d", my_rank);
	fp = fopen(f_name, "w");

	for (i = 0; i < BUF_SIZE; i++) {
		fprintf(fp, "%d ", buf[i]);
	}
	fprintf(fp, "\n");

	fclose(fp);

	return 0;
}

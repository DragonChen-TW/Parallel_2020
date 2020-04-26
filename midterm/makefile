c_mpi:
	mpicc -o c_mpi.out ./q5_mpi.c
c_mpi_run:
	mpirun -n 25 ./c_mpi.out
c_arr:
	gcc -o c_arr.out ./q5_array.c
c_thread:
	gcc -o c_thread.out ./q5_thread.c
py_mpi:
	mpiexec -n 50 pipenv run python py_mpi.py
py_arr:
	pipenv run python py_arr.py
py_thread:
	pipenv run python py_thread.py

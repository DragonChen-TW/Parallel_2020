from mpi4py import MPI
import numpy as np
#
from q2_mosaic import read_pgm, save_pgm

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
#
length = 256 # img size
tag = 10
cores = 64
header_bytes = 12 # ignore 3 ints

length_per_core = int(cores ** 0.5)
x_rank = rank // length_per_core
y_rank = rank % length_per_core
ints_per_core = length // length_per_core

def make_mosaic(data, l, size=4):
    for i in range(0, data.shape[1] - (size - 1), size):
        for j in range(0, data.shape[0] - (size - 1), size):
            avg = int(np.average(data[i:i+size, j:j+size]))
            data[i:i+size, j:j+size] = avg

    l2 = l
    return l2, data

if __name__ == '__main__':
    if rank == 0:
        print('Start reading')
        print('header_bytes', header_bytes)
        print('ints_per_core', ints_per_core)

    amode = MPI.MODE_RDONLY
    fp = MPI.File.Open(comm, './lennabinary.pgm', amode)

    sub_data = np.empty(ints_per_core, dtype='i')

    offset = header_bytes + rank * ints_per_core * 4
    # print(rank, offset)
    fp.Read_at(offset, sub_data)

    avg = int(np.average(sub_data))
    # print('avg', avg)
    sub_data[:] = avg

    fp.Close()
    amode = MPI.MODE_CREATE | MPI.MODE_WRONLY
    fp = MPI.File.Open(comm, './lenna_out.pgm', amode)

    # fp.Write_at(offset, sub_data)

    # if rank == 0:
    #     # join all
    #
    save_pgm(f'q2_out/lenna{length_per_core}x{length_per_core}lenna_mosaic{rank}.pgm', 'P2', int(ints_per_core ** 0.5), 255, sub_data)

from mpi4py import MPI
import numpy as np
import matplotlib.pyplot as plt

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

if __name__ == '__main__':
    np.random.seed(rank) # init with rank

    test_times = 200
    test_size = 100

    # make random from 0 to 1, size is 1-d (test_size)
    data = np.random.rand((test_size))
    avg = np.average(data).astype('f')
    # print(rank, avg, type(avg))
    results = None

    # if rank == 0, change receive buf to an array
    if rank == 0:
        results = np.zeros(test_times, dtype='f')

    # Send all data to root
    comm.Gather(avg, recvbuf=results, root=0)
    if rank == 0:
        print(results)
        # plt.plot(range(test_times), results)
        plt.xlim(0.4, 0.6)
        plt.hist(results)
        plt.show()

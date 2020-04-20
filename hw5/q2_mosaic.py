from mpi4py import MPI
import numpy as np

def read_pgm(f_name):
    with open(f_name) as f:
        mode = f.readline()[:-1]
        lenx, leny = [int(c) for c in f.readline()[:-1].split()]
        max_value = int(f.readline()[:-1])
        print(lenx, leny, max_value)
        print(type(lenx), type(leny), type(max_value))

        # not stable for all case, I guess
        nums = ''.join(f.readlines())
        nums = nums.replace('\n', '').split()
        nums = np.array([int(n) for n in nums])

        size = 256 # 256x256 pixels
        # nums = [nums[s:s + size] for s in range(0, len(nums), size)] # no numpy
        nums = nums.reshape((size, size))

    return mode, lenx, max_value, nums

def save_pgm(f_name, mode, length, max_value, data):
    with open(f_name, 'w') as f:
        f.write(f'{mode}\n')
        f.write(f'{length} {length}\n')
        f.write(f'{max_value}\n')
        data_str = data.reshape(-1).tolist()
        data_str = ' '.join([str(n) for n in data_str])
        f.write(f'{data_str}')

def make_mosaic(data, l, size=4):
    for i in range(0, data.shape[1] - (size - 1), size):
        for j in range(0, data.shape[0] - (size - 1), size):
            avg = int(np.average(data[i:i+size, j:j+size]))
            data[i:i+size, j:j+size] = avg

    l2 = l
    return l2, data

# non-MPI way
if __name__ == '__main__':
    m_size = 4
    mode, l, max_value, data = read_pgm('lenna.pgm')
    l2, data2 = make_mosaic(data, l, m_size)
    save_pgm(f'lenna_mosaic{m_size}.pgm', mode, l2, max_value, data2)
    l2, data2 = make_mosaic(data, l, m_size * 2)
    save_pgm(f'lenna_mosaic{m_size*2}.pgm', mode, l2, max_value, data2)

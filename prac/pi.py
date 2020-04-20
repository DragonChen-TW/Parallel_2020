import math, time
import random

def get_pi():
    len_x = len_y = 10
    mid = (len_x / 2, len_y / 2)
    max_points = 1000000 # 10W
    in_points = 0

    def dist(x, y):
        temp = (y[0] - x[0]) ** 2 + (y[1] - x[1]) ** 2
        return temp ** 0.5

    for _ in range(max_points):
        x = random.random() * 10
        y = random.random() * 10

        if dist((x, y), mid) <= len_x / 2:
            in_points += 1

    # print(in_points / max_points)
    print('Eval pi', in_points / max_points * 4)

if __name__ == '__main__':
    t = time.time()
    print('True pi', math.pi)
    get_pi()
    print('Cost', time.time() - t, 'secs')

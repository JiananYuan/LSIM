import csv
import sys
import os
import numpy as np
import random
import argparse


def generate_data(_selectivity, _n):
    # if not os.path.exists('dataset'):
    #     print('path do not exist, create new directory!')
    #     os.mkdir('dataset')
    # csv_path = 'dataset/' + _selectivity + '.csv'
    csv_path = str(_selectivity) + "_" + str(_n) + '.csv'
    n = int(_n)
    # m = int(_m)
    selectivity = float(_selectivity)
    g = int(n * selectivity)  # group number
    s_index = 1
    with open(csv_path, 'w', newline='') as f:
        writer = csv.writer(f)
        # header = [[]]
        # for _i in range(0, m):
        #     header[0].append(chr(65 + _i))  # A, B, C, ....
        data = []
        for _i in range(1, n + 1):
            if _i % (n / g) == 0:
                s_index += 1
            # for _j in range(0, m - 2):
            #     tmp.append(0)
            data.append([_i, s_index])
        random.shuffle(data)
        # header.extend(data)
        writer.writerows(data)


# python3 datagen.py seg1 1000000
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-s", "--selectivity", help="selectivity", dest="_selectivity", type=float, default="1")
    parser.add_argument("-n", "--number_of_records", help="number of records", dest="_n", type=int, default="1")
    # parser.add_argument("-m", "--number_of_attributes", help="number of attributes", dest="_m", type=int, default="1")
    args = parser.parse_args()
    _selectivity = args._selectivity  # 选择度
    _n = args._n  # 数据size
    # _m = args._m  # 属性个数
    print("args._selectivity: ", _selectivity)
    print("args._n: ", _n)
    # print("args._m: ", _m)
    generate_data(_selectivity, _n)
    print("ok")

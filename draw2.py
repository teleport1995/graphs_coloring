import matplotlib.pyplot as pl

data = list(map(float, open("log.txt").read().split("\n")[:-1]))
pl.xlabel('n')
pl.ylabel('Время работы алгоритма, сек.')
pl.xlim([0, 10000])
pl.ylim([0, 5])
pl.plot([i * 200 for i in range(1, 51)], [data[4*i+0] for i in range(50)], 'r', label='4.1')
pl.plot([i * 200 for i in range(1, 51)], [data[4*i+1] for i in range(50)], 'g', label='4.2')
pl.plot([i * 200 for i in range(1, 51)], [data[4*i+2] for i in range(50)], 'b', label='4.3')
pl.plot([i * 200 for i in range(1, 51)], [data[4*i+3] for i in range(50)], 'y', label='4.4')
pl.legend()
pl.show()
import matplotlib.pyplot as pl

data = open("log.txt").read().split("\n")
pl.title(data[0])
data = data[1:-1]
print(data[0].split()[1])
pl.xlabel('Число потоков, ед.')
pl.ylabel('Время работы алгоритма, сек.')
pl.xlim([0, len(data) + 1])
pl.ylim([0, max([float(x.split()[1]) + .1 for x in data])])
pl.plot([int(x.split()[0]) for x in data], [float(x.split()[1]) for x in data], 'r')
pl.legend()
pl.show()

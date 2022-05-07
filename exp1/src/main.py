from matplotlib import pyplot as plt

prefix = './target/'
name_list = ['enumerate', 'graham_scan', 'divide_and_conquer']
num_list = [100]
suffix = '.txt'

for name in name_list:
    for num in num_list:
        path = prefix + name + '_' + str(num) + suffix
        x, y = [], []

        px, py = [], []

        with open(path, 'r') as f:
            n = int(f.readline())
            for _ in range(n):
                t = f.readline().split(' ')
                if len(t) != 2:
                    print(t)
                    exit(0)
                x.append(float(t[0]))
                y.append(float(t[1]))
            n = int(f.readline())
            for _ in range(n):
                t = f.readline().split(' ')
                if len(t) != 2:
                    print(t)
                    exit(0)
                px.append(float(t[0]))
                py.append(float(t[1]))
            px.append(px[0])
            py.append(py[0])

        plt.scatter(x, y, s=5, c='b')
        plt.plot(px, py)
        plt.scatter(px, py, s=15, c='r')
        import os
        if not os.path.exists('./picture'):
            os.mkdir('./picture')
        plt.savefig('./picture/' + name + '_' + str(num) + '.jpg')
        plt.clf()

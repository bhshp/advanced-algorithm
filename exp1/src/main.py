from matplotlib import pyplot as plt

for i in range(1, 5 + 1):
    x, y = [], []

    with open('./data/' + str(i) + '.in', 'r') as f:
        n = int(f.readline())
        for _ in range(n):
            t = f.readline().split(' ')
            if len(t) != 2:
                print(t)
                exit(0)
            x.append(float(t[0]))
            y.append(float(t[1]))

    px, py = [], []

    with open('./target/' + str(i) + '.out', 'r') as f:
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
    plt.savefig('./picture/' + str(i) + '.jpg')
    plt.clf()

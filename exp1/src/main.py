from matplotlib import pyplot as plt

x, y = [], []

with open('./data/1.in', 'r') as f:
    n = int(f.readline())
    for _ in range(n):
        t = f.readline().split(' ')
        if len(t) != 2:
            print(t)
            exit(0)
        x.append(float(t[0]))
        y.append(float(t[1]))

px, py = [], []

with open('./target/1.out', 'r') as f:
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
plt.savefig('./picture/1.jpg')

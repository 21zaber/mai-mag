l = []

x, y = 3, 3

mv = [
    (1, 2),
    (1, -2),
    (-1, 2),
    (-1, -2),
    (-2, 1),
    (-2, -1),
    (2, -1),
    (2, 1),
]

def check(x, y, a, b):
    return 0 <= x+a < 8 and 0 <= y+b < 8

mask = [[0 for i in range(8)] for i in range(8)]

ln = 0

def dfs(x, y):
    global ln, l, mask
    ln += 1
    mask[x][y] = 1
    l.append((x, y))

    if ln == 64:
        print(l)
        exit(0)

    for a,b in mv:
        if check(x, y, a, b) and mask[x+a][y+b] == 0:
            dfs(x+a, y+b)

    ln -= 1
    mask[x][y] = 0
    l = l[:-1]


dfs(x, y)



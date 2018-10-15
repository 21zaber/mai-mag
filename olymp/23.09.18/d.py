x1, y1 = map(int, input().split())
x2, y2 = map(int, input().split())

def _solve(x, y):
    t = y + 2 * x 
    if t % 5 == 0:
        i = t // 5
        return i, x - 2 * i
    else:
        return None 

def solve(x, y):
    l = [[0, 0], [1, 0], [-1, 0], [0, 1], [0, -1]]

    for k in l:
        nx = x + k[0]
        ny = y + k[1]
        r = _solve(nx, ny)
        if r is not None:
            return r



rx1, ry1 = solve(x1, y1)
rx2, ry2 = solve(x2, y2)

#   print(rx1, ry1)
#   print(rx2, ry2)

print(abs(rx1-rx2) + abs(ry1-ry2))

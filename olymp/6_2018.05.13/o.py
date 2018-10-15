n =int(input())

x, y = map(int, input().split())
x1, y1 = map(int, input().split())

dir = None
if x == x1:
    dir = 1
else:
    dir = 2

ans = 0


for i in range(n-2):
    x, y = map(int, input().split())

    if dir == 1 and x != x1:
        ans += 1
        dir = 3 - dir
    elif dir == 2 and y != y1:
        ans += 1
        dir = 3 - dir
    #print(x, y, ans, dir)
    x1, y1 = x, y

print(ans)

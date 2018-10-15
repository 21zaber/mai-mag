t = int(input())

for i in range(t):
    x = int(input())
    a = 1
    b = 1
    c = 1

    if abs(x) < 100:
        c = -x*x -x

    elif x > 0:
        b = -x + 1
        c = -x
    else:
        b = -x - 1
        c = x
    
    print(a, b, c)





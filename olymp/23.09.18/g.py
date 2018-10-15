n, d = map(int, input().split())

def x(n, b, e):
    c = n // b
    t = n - (c * b)

    if t == e:
        if b-1 == e:
            return '1{}{}'.format(t-1, str(b)*c)
        return '{}{}{}'.format(t+1, b-1, str(b)*(c-1))

    return int('{}{}'.format(t, str(b)*c))

if n ==  d:
    print('1{}'.format(n-1))
elif d == 9:
    print(x(n, 8, d))
else:
    print(x(n, 9, d))



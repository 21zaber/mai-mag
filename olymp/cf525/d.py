
from sys import stdout
a, b = 0, 0


mp = 29

c, d = 0,0

powers = [1]
for i in range(32):
    powers.append(powers[-1]*2)

qqq = 0

def get_ans(c, d):
    global qqq
    qqq += 1
    a, b = 1073741823, 1073741821
    a, b = 3, 1

    print(c, d)

    if (a^c) > (b^d): 
        print(1)
        return -1
    elif (a^c) < (b^d):
        print(-1)
        return 1
    print(0)
    return 0

def get_ans(c, d):
    print('? {} {}'.format(c, d))
    stdout.flush()
    return -int(input())

q = get_ans(0, 0)

for i in range(mp+1):
    cp = mp - i
    c += powers[cp]
    d += powers[cp]
    #print('cp, q', cp, q)
    if q == 0:
        continue
    t = get_ans(c, d)
    #print('t', t)

    if t != q:
    #    print('t != q')
    #    print(a, b,c,d)
        if t == 1:
            a += powers[cp]
            c -= powers[cp]
        elif t == -1:
            b += powers[cp]
            d -= powers[cp]
        q = get_ans(c, d)

    #print(a, b, c, d)

#print('qwe', a, b, c, d)


for i in range(mp+1):
    cp = mp - i
    #print(c, powers[cp], d)
    if c & powers[cp] > 0 and d & powers[cp] > 0:
        c -= powers[cp]
        t = get_ans(c, d)

        if t < 0:
            a += powers[cp]
            b += powers[cp]

        c += powers[cp]

print('!', a, b)



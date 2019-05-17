from math import sqrt

def u(x):
    
    for i in range(2, int(sqrt(x)) + 1):
        if x % (i*i) == 0:
            #print(x, i*i)
            return 0
    
    return 1

def prime(x):
    for i in range(2, int(sqrt(x))+1):
        if i < x and x % i == 0:
            return False
    return True

def get_test():
    ss = ''

    for i in range(1, 10**4):
        ss += str(u(i))

    return ss

def try(s, d):
    t = set()
    for k, v in d.items():
        t.update({s[i] == '0' for i in range(v, 200, k)})

    for i in range(len(s)):
        if not ((i == '0' and i in t) or (i =='1' and i not in t)):
            return False

    return True

def perm(d):

    t = {}
    k = list(d.keys())[0]


def ans(s):
    from collections import defaultdict
    d = defaultdict(set)

    for i in range(2, 15):
        q = i*i
        if not prime(i):
            continue

        for j in range(200):
            if all([s[k]=='0' for k in range(j%q, 200, q)]):
                d[q].add(j)

        for k in d:
            if q % k == 0:
                d[q] &= d[k]


        if not d.get(q):
            return False

    l = [i for i in d]
    l.sort()

    dd = {}

    for k in l:
        md = set()
        q = []
        for i in d[k]:
            if i % k not in md:
                md.add(i%k)
                q.append(i)

        dd[k] = q

    print(dd)


    return True

if not True:
    q = get_test()

    for i in range(8000):
        t = ans(q[i:i+200])
        if not t:
            print(i)
            print(q[i:i+200])
            break
    exit(0)

s = ''
for i in range(10):
    s += input()

if ans(s):
    print(1)
else:
    print(-1)





from random import choice
from copy import deepcopy as copy
from pprint import pprint

n = int(input())

# convert vector to int
def to_int(v):
    p = 1
    a = 0
    for i in v[::-1]:
        a += p * ((i+1)//2)
        p *= 2
    return a

# convert int to vector
def from_int(a):
    v = []
    while a > 0:
        v = [int((a % 2 - 0.5)*2)] + v
        a //= 2
    if len(v) < n:
        v = [-1 for i in range(n - len(v))] + v
    return v

def check(a, b):
    c = a ^ b
    oc = 0
    while c > 0:
        oc += c & 1
        c >>= 1

    return oc == n // 2

# get next vector
def next(v):
    return from_int(to_int(v) + 1)

# generate all vectors
total = 2 ** n
vects = [i for i in range(total)]

lst_vect = None
m = []
cur_vects = []

print("Step 0. Current size of vector's list - {}".format(len(vects)))

for step in range(n):
    if lst_vect is None:
        lst_vect = choice(vects)
        m.append(lst_vect)

        for v in vects:
            if not check(v, lst_vect):
                cur_vects.append(v)
    else:
        lst_vect = choice(cur_vects)
        m.append(lst_vect)
    
        old_vects = copy(cur_vects)
        cur_vects = []
        for v in old_vects:
            if check(v, lst_vect):
                cur_vects.append(v)
    print("Step {}. Current size of vector's list - {}".format(step+1, len(cur_vects)))
    if len(cur_vects) == 0:
        print("Failed to find matrix of a given dimension {}".format(n))
        exit(0)

m = [from_int(i) for i in m]

pprint(m)


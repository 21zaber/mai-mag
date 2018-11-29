a1, b1, c1 = map(int, input().split())
a2, b2, c2 = map(int, input().split())

c1 *= -1
c2 *= -1
from math import sqrt

def n(a,b,c):
    if a == 0:
        return (0, 1)
    if b == 0:
        return (1, 0)

    x = sqrt(a**2 + b**2)
    return (a/x, b/x)

def l(a, b, c):
    return -c/(sqrt(a**2 + b**2))

v1 = n(a1,b1,c1)
l1 = l(a1, b1, c1)
v1 = (v1[0]*l1, v1[1]*l1)
v2 = n(a2,b2,c2)
l2 = l(a2, b2, c2)
v2 = (v2[0]*l2, v2[1]*l2)

print(l1, l2, v1, v2)


ll = l1 + l2 + sqrt((v1[0] - v2[0]) ** 2 + (v1[1] - v2[1])**2)

if b1 * a2 == b2 * a1:
    print(ll)
    exit(0)

y = -(c1*a2 - a1*c2) / (b1*a2 - a1*b2)
x = 0

if a1 and b1:
    x = (-c1 - b1*y) / a1
elif a2 and b2:
    x = (-c2 - b2*y) / a2
else:
    if a1:
        x = -c1 / a1
    else:
        x = -c2 / a2

print(v1, v2, (x,y))

t = 0.1 ** 15

def check1(m1):
    l, r = 0, 1

    while abs(r - l) > t:
        c1 = (r - l) * 1 / 3 + l
        c2 = (r - l) * 2 / 3 + l

        ans1 = check2(m1, c1)
        ans2 = check2(m1, c2)

        if ans1 < ans2:
            r = c2
        else:
            l = c1 

    return l



def check2(m1, m2):
    x1 = (x - v1[0]) * m1 + v1[0]  
    y1 = (y - v1[1]) * m1 + v1[1]  
    x2 = (x - v2[0]) * m2 + v2[0]  
    y2 = (y - v2[1]) * m2 + v2[1] 

    #print(x1, y2, x2, y2)

    return sqrt(x1**2 + y1**2) + sqrt(x2**2 + y2**2) + sqrt((x1-x2)**2 + (y1-y2)**2)


l, r = 0, 1

ans = 0

while abs(r - l) > t:
    c1 = (r - l) * 1 / 3 + l
    c2 = (r - l) * 2 / 3 + l

    ans1 = check1(c1)
    ans2 = check1(c2)

    ans = check2(c1, ans1)

    if ans < check2(c2, ans2):
        r = c2
    else:
        l = c1

print(ans)


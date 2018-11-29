n = int(input())

a = list(map(int, input().split()))

a = [1] + a + [1]

MX = 10

def check(l):
    for i in range(1, n+1):
        if l[i] > max(l[i-1], l[i+1]):
            return 0

    print(l)

    return 1


def ans(l, p):
    if p >= len(l):
        return int(check(l))

    if l[p] != -1:
        return ans(l, p+1)

    a = 0

    for i in range(1, MX+1):
        l[p] = i
        a += ans(l, p+1)

    l[p] = -1

    return a

print(ans(a, 1))


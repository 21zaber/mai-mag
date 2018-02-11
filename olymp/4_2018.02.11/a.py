n,s = map(int, input().split())

seq = list(map(int, input().split()))

p = int(input())
p = list(map(int, input().split()))
q = int(input())
q = list(map(int, input().split()))
p.sort(reverse=True)
q.sort(reverse=True)

ult = [0 for i in range(2*n)]
smpl = [0 for i in range(2*n)]

INF = 10**10


def ans(i, ip, iq):

    if i >= len(seq):
        return 0

    pl = seq[i]-1

    if pl < n: 
        a = [-INF, -INF]
        if (smpl[pl] < s):
            smpl[pl] += 1
            a[0] = p[ip] + ans(i+1, ip+1, iq)
            smpl[pl] -= 1
        if (ult[pl] == 0):
            ult[pl] = 1
            a[1] = q[iq] + ans(i+1, ip, iq+1)
            ult[pl] = 0

        if a[0] > a[1]:
            return a[0]
        else:
            return a[1]
    else:
        a = [INF, INF]
        if (smpl[pl] < s):
            smpl[pl] += 1
            a[0] = -p[ip] + ans(i+1, ip+1, iq)
            smpl[pl] -= 1
        if (ult[pl] == 0):
            ult[pl] = 1
            a[1] = -q[iq] + ans(i+1, ip, iq+1)
            ult[pl] = 0
        if a[0] < a[1]:
            return a[0]
        else:
            return a[1]


print(ans(0, 0, 0))


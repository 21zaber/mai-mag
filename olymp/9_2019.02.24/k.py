s = input()

n = int(input())


idx = list(map(lambda x: int(x)-1, input().split()))

ans = ''

bad = s[idx[-1]]
good = s[idx[-1]]

for i in range(n-1, -1, -1):
    if not i:
        ss = s[:idx[i]+1]
    else:
        ss = s[idx[i-1]+1:idx[i]+1]
    ca = ''
    d = {}

    print(ss)

    for j in range(len(ss)):
        if j == len(ss)-1 or (ss[j] <= good and ss[j] <= bad):
            if ca and ss[j] < ca[0]:
                d = {}
                d[ss[j]] = 0
                ca = ss[j]
            elif ss[j] in d:
                for k in ca[d[ss[j]]+1:]:
                    del d[k]
                ca = ca[:d[ss[j]]+1] + ss[j]
                d[ss[j]] = len(ca)-1
            else:
                p = len(ca)
                for k in ca[::-1]:
                    if k > ss[j] and k in d:
                        del d[k]
                    else:
                        break
                    p -= 1
                ca = ca[:p] + ss[j]
                d[ss[j]] = len(ca)-1

        print(ss, ca, d, ans)

    ans = ca + ans
    for i in ca+ss[-1]:
        if i > bad:
            bad = i
    if ans[0] < good:
        good = ans[0]

    print(good, bad)

print(ans)




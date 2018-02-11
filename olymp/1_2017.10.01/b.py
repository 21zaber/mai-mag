t = int(input())
for i in range(t):
    n = int(input())

    s = [input() for i in range(n)]

    l = max([len(i) for i in s])

    s.sort(key=len)
    t = True

    for i in range(1, n):
        s1, s2 = s[i-1], s[i]
        l1, l2 = len(s1), len(s2)
        if s2[:l1] != s1:
            print("Impossible")
            t = False
            break

    if t:
        print(l)


syms = ['S', 'E', 'W', 'N']

def f(s):

    d = {}
    for i in s:
        if i not in syms:
            continue

        d[i] = True

    if len(d) == 1:
        return 'X'
    else:
        return ''.join(list(set(syms) - set(d.keys())))

import random
for i in range(100):
    s = ''.join([random.choice(syms) for i in range(4)])
    ans = f(s)

    print(s, ans)


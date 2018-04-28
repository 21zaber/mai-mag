prior = [3,3,4,4,3,3]

def get_prior(x, y):
    return prior[y] - x // 2

px, py, pa = 0,0,0
m = []

for x in range(6):
    s = input()
    m.append(list(s))
    s = s.replace('-', '')
    for y in range(6):
        p = get_prior(x, y)
        if s[y] == '.' and p > pa:
            px, py, pa = x, y, p

if py > 3:
    py += 2
elif py > 1:
    py +=1

m[px][py] = 'P'

for i in m:
    print(''.join(i))




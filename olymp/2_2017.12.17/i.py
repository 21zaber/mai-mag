s = input().strip()

syms = {'S', 'E', 'W', 'N'}

d = {}
for i in s:
    if i not in syms:
        continue

    d[i] = True

if len(d) < 2:
    print('X')
elif len(d) == 2:
    if ('S' in d and 'N' in d) or ('E' in d and 'W' in d):
        print('X')
    else:
        print(''.join(list(syms - set(d.keys()))))
else:
    print(''.join(list(syms - set(d.keys()))))

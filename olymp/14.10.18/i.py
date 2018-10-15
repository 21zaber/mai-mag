n = int(input())

# 0 - first, 1 - second
w = [1, 0, 0, 0]
e = [0, 1, 1, 0]

for i in range(5, 20):

    print(i, ':')	
    ans = 1
    for l in range(i-2):
        r = i-2-l
        if l > r:
            break
        
        lw = w[l-1]
        ll = e[l-1]
        rw = w[r-1]
        rl = e[r-1]
        if (lw == rw and ll == rl):
            ans = 0
            print('\tw', l, r, 0)
            break
    w.append(ans)

    ans = -1
    for l in range(i-2):
        r = i-2-l
        if l > r:
            break
        lw = w[l-1]
        ll = e[l-1]
        rw = w[r-1]
        rl = e[r-1]
        if (lw == rw and lw == 0 and ll == rl):
            ans = 0
            print('\tl', l, r, 0)
            break
        if (lw == rw and lw == 0 and ll == rl):
            ans = 0
            print('\tl', l, r, 0)
            break
    e.append(ans)



print('[{}]'.format(','.join(list(map(str, w)))))
print('[{}]'.format(','.join(list(map(str, e)))))
print('[{}]'.format(','.join(list(map(str, [i for i in range(1,10)])))))



for i in range(n):
    a = int(input())

    if t[a-1]:
        print('Second')
    else:
        print('First')

    


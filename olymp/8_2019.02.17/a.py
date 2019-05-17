
import sys
n = int(input())

count = 0
cache = {}

def ask(l):
    global count
    l = [i+1 for i in l]
    for i in range(len(l)):
        if l[i] == 0:
            l[i] = n
        if l[i] == n+1:
            l[i] = 1

    l.sort()

    if tuple(l) in cache:
        return cache[tuple(l)]

    count += 1

    print('? {}'.format(len(l)))
    print(' '.join(list(map(str, l))))

    sys.stdout.flush()

    s = float(input())
    s = round(2*s)

    cache[tuple(l)] = s
    return s

def ans(a):
    print('!', a/2)
    sys.stdout.flush()
    print(count)
    exit(0)




def calc_ans(l, upper_mm):
    print('calc_ans', l)
    if len(l) < 3:
        
        #print('return', 0)
        return 0

    sq = ask(l)

    if len(l) == 3:
        #print('return', sq)
        return sq

    mm = [1 for i in range(n)]

    for j in l:
        if not upper_mm[j]:
            s = ask([i for i in l if i != j])
            if s == sq:
                mm[j] = 0

    subl = []
    end = n

   # print(mm)

    if not mm[0]:
        i = n-1
        subl.append(i)
        while not mm[i]:
            i -= 1
            subl.append(i)

        end = i

    #print(subl)

    i = 0
    while i < end:
        if mm[i]:
            subl.append(i)
            sq -= calc_ans(subl, mm)
            subl = [i]
            i += 1
            continue
        subl.append(i)
        i+=1

    print('return', sq)
    return sq



ans(calc_ans([i for i in range(n)], [0 for i in range(n)]))

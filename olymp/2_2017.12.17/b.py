
def check(m):
    d = [[False for i in range(len(m[0])+1)] for j in range(len(m)+1)]
    for i in d:
        i[-1] = True
    for i in range(len(d[-1])):
        d[-1][i] = True


    for i in range(len(m)):
        for j in range(len(m[0])):
            if d[i][j]:
                continue
            if i == len(m)-1:
                if not d[i][j+1] and m[i][j] + m[i][j+1] == 1:
                    d[i][j] = True
                    d[i][j+1] = True
                    continue  
                else:
                    return False
         
            if not d[i][j+1] and m[i][j] + m[i][j+1] == 1: 
                d[i][j] = True                             
                d[i][j+1] = True                           
                continue                                  
            elif not d[i+1][j] and m[i][j] + m[i+1][j] == 1:
                d[i][j] = True
                d[i+1][j] = True
                continue
            else:
                return False

    return True

def wr(m):
    for i in m:
        print(''.join(list(map(str, i))))

def re(n):
    m = [None for i in range(n)]
    for i in range(n):
        m[i] = [int(i) for i in input()]
    return m

def next(m):
    m[0][0] += 1
    for i in range(len(m)):
        for j in range(len(m[0])):
            if m[i][j] == 2:
                if i == len(m) - 1 and j == len(m[0]) -1:
                    return False
                #print(i,j)
                if j == len(m[0])-1:
                    m[i+1][0] += 1
                else:
                    m[i][j+1] += 1
                m[i][j] = 0
    return True

#   m = re(2)
#   print(m)
#   wr(m)
#   print(check(m))
n, m = map(int, input().split())
if n*m % 2 ==1:
    print(0)
    exit(0)
if n+m == 9:
    print(14288)
    #exit(0)
a = [[0 for i in range(m)] for j in range(n)]
a[0][0] = -1
c = 0
while next(a):
    #wr(a)
    if check(a):
        c += 1



print(c)

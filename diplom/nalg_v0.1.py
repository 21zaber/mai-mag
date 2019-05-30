import sys
import time

gc = 0 # tries count

# set to True for verbose mode
DEBUG = False

def mprint(m):
    # simple print matrix
    
    for i in m:
        print(' '.join(list(map(str, i))))

def print_sle(a, b):
    # print SLE with x1-xn

    if not DEBUG:
        return

    for ii, i in enumerate(a):
        s = ''
        for j in range(len(i)):
            s += ' {}*x{} +'.format(i[j], j)
    
        if s.endswith('+'):
            s = s[:-1]
    
        s += '= {}'.format(b[ii])
    
        print(s)


def gauss(a, b, x):
    # try to solve SLE A*x=b
    # return True if solution exists and False else
    #
    # some of x can be known numbers, some eq None (unknown)

    if DEBUG:
        print('before x')
        print_sle(a, b)
    
    # remove known x's from SLE
    for i in range(len(x)):
        if x[i] is None:
            continue

        for j in range(len(a)):
            b[j] -= a[j][i] * x[i]
            a[j][i] = 0

    if DEBUG:
        print(x)
        print('after x')
        print_sle(a, b)

    # sort columns
    # sort in descending order of number of zeros in column
    ta = [[a[i][j] for i in range(len(a))] for j in range(len(a[0]))]   # transpose
    ta.sort(key=lambda x: sum([bool(i) for i in x]))                    # sort
    a = [[ta[i][j] for i in range(len(ta))] for j in range(len(ta[0]))] # transpose

    # index of last column we processed
    last_c = 0   
    for i in range(len(a)-1):
        col = last_c + 1

        # search for correct column
        j = None
        while j is None and col < len(a[0]):
            # search for first non-0 cell
            for i in range(len(a)):
                if a[i][col]:
                    j = i
                    break

            if j is None:
                col += 1

        if not j:
            break

        # set column to zero
        for i in range(j+1, len(a)):
            # subtract from i-row j-row
            if a[i][col] == 0:
                continue

            m = a[i][col] / a[j][col]

            for k in range(col, len(a[0])):
                a[i][k] -= a[j][k] * m

            b[i] -= b[j] * m

        last_c = col

    if DEBUG:
        print('after gauss')
        print_sle(a, b)

    # look for discrepancy
    for i in range(len(a)):
        if sum([bool(j) for j in a[i]]) == 0 and abs(b[i]) > 0.0000001:
            return False

    return True

def mtry(m, x, y, v):
    # create SLE and run Gauss

    global gc
    gc += 1

    xx = [None for i in range(len(m[0]))]
    for i in range(y):
        xx[i] = [-1, 1][m[x][i]]
    xx[y] = [-1, 1][v]

    a = [[[-1, 1][i] for i in j] for j in m[:x]]

    f = gauss(a, [0 for i in range(x)], xx)

    if DEBUG:
        print('mtry:', x, y, v, f)
        print()

    return f

n = int(sys.argv[1])

# start timestamp
sts = time.time()

# out matrix
matrix = [[None for i in range(n)] for i in range(n)]
# None means unknown cell

# fill first 3 rows of matrix
# Example for n==12:
# 1 1 1 1 1 1 1 1 1 1 1 1
# 1 1 1 1 1 1 0 0 0 0 0 0
# 1 1 1 0 0 0 1 1 1 0 0 0

matrix[0] = [1 for i in range(n)]

for i in range(n//2):
    matrix[1][i] = 1
for i in range(n//2, n):
    matrix[1][i] = 0

for i in range(n//4): matrix[2][i] = 1
for i in range(n//4, n//2): matrix[2][i] = 0
for i in range(n//2, 3*n//4): matrix[2][i] = 1
for i in range(3*n//4, n): matrix[2][i] = 0



# start posision
i, j = 3, 0

cbc = 0 # comeback count

try:
    while i > 2 and i < n:
        while j < n:
            # try to set 1
            if mtry(matrix, i, j, 1):
                matrix[i][j] = 1
                j += 1
            # try to set 0
            elif mtry(matrix, i, j, 0):
                matrix[i][j] = 0
                j += 1
            # else comeback inside current row
            else:
                # column comeback
                while j > 0 and not (matrix[i][j-1] == 1 and mtry(matrix, i, j-1, 0)):
                    j -= 1
                    cbc += 1

                # failed to comeback in that row
                if j == 0:
                    break

                # success comeback
                matrix[i][j-1] = 0

        if j < n:
            # row comeback
            j = n - 1
            i -= 1

            while i > 2:
                # column comeback
                while j >= 0 and not (matrix[i][j] == 1 and mtry(matrix, i, j, 0)):
                    j -= 1
                    cbc += 1

                if j >= 0:
                    # success comeback
                    matrix[i][j] = 0
                    j += 1
                    break

                # failed to comeback in that row
                i -= 1
        else:
            # row successfully filled, go to next one
            j = 0
            i += 1
except KeyboardInterrupt:
    # try with KbI catching for correct stopping
    pass



print('total time', time.time() - sts)
mprint(matrix)
print(i, j)
print('total comebacks', cbc)
print('total tries', gc)

input()
a = input()[::-1]
b = input()
t = int(input())

if t == 0:
    print(a + b)
    exit(0)

ansl = ''
ansr = ''

if len(a) > t:
    ansl = a[:-t]
    a = a[-t:]

if len(b) > t:
    ansr = b[t:]
    b = b[:t]

#print(ansl, a)
#print(b, ansr)

s = [i for i in a] + [i for i in b]
l = [0 for i in range(len(a))] + [1 for i in range(len(b))]

for i in range(t):
    j = 1
    ln = len(s)
    while j < ln:
        if l[j] > l[j-1]:
            s[j], s[j-1] = s[j-1], s[j]
            l[j], l[j-1] = l[j-1], l[j]
            j += 1

        j += 1

#    print(''.join(s))

print(ansl + ''.join(s) + ansr)

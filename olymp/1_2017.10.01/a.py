n = int(input())

def conv(s):
    a = 0
    if s[0] == '1':
        a += 8
    if s[1] == '1':
        a += 4
    if s[2] == '1':
        a += 2
    if s[3] == '1':
        a += 1

    return a

def conv2(s):
    a = conv(s)
    if a < 10:
        return str(a)
    return chr(ord('A')+a-10)

for i in range(n):
    s = input()
    if len(s) % 4:
        s = '0'*(4-len(s)%4) + s

    ans = ''
    for i in range(len(s) // 4):
        ss = s[4*i:4*(i+1)]
        ans += conv2(ss)

    print(ans)

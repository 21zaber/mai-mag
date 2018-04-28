s = input()
n = int(input())

t = [['1', 'l', 'i'], ['o', '0']]

g = True

for i in range(n):
    nick = input()

    if len(s) != len(nick):
        continue
    
    f = True

    for i in range(len(s)):
        if s[i].lower() == nick[i].lower():
            continue
        if s[i].lower() in t[0] and nick[i].lower() in t[0]:
            continue
        if s[i].lower() in t[1] and nick[i].lower() in t[1]:
            continue
        f = False
        break

    if f:
        g = False
        break

if g:
    print("Yes")
else:
    print("No")


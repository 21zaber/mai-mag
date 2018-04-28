t, k = map(int, input().split())

def round(a):
    if a > int(a):
        return int(a) + 1
    return int(a)

x = round(t + (t+1)/(k))
if k >= t:
    print(x)
else:
    print(x)

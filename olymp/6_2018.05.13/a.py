t = int(input())

def f (n, k, d):
    return n - (k-1)*d

for i in range(t):
    n, k = map(int, input().split())
    if k > n:
        print(0)
        continue

    if k == 1:
        print(n)
        continue

    x = int(n / (k-1))
   #for i in range(x):
   #    print(n, k, i+1, f(n, k, i+1))
   #continue

    print(n * x - (k-1) * x * (x+1) // 2)

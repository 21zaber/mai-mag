n, k = map(int, input().split())

def c(n, k):
   a = 1

   for i in range(k+1, n+1):
       a * = i
       a /= i-k

    return a


p = 1/ 3

for i in range(k):


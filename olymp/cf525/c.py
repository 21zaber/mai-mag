n = int(input())

l = list(map(int, input().split()))


p = 1

t = 400 * 1000
mx = t + len(l)

p = 0

#q = [i for i in l]

print(n+1)

for i in range(n-1, -1, -1):
    a = mx - ((p + l[i]) % t)
   #for j in range(i+1):
   #    q[j] += a
    print(1, i+1, a)
    p += a
    mx -= 1


print(2, n, t)

#q = [i%t for i in q]

#print(q)
    
        
    

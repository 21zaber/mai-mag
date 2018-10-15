tf = open('test', 'r')
n, d = map(int, tf.readline().split())

ans = input()
if str(d) in ans:
    print('FAIL', n, d)
if sum(list(map(int, list(ans)))) != n:
    print('FAIL2', n, d)



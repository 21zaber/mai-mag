n = int(input())
x, y = map(int, input().split())


if max(x, y)-1 <= max(n-x, n-y):
    print('White')
else:
    print('Black')

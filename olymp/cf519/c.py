s = input()

#   def ans(s):
#   #    print(s)
#       if len(s) < 2:
#           return [0]
#
#       if s[-1] == 'a':
#           t = ans(s[:-1])
#           t[-1] = 1 - t[-1]
#           t += [1]
#           return t
#       return ans(s[:-1]) + [0]

ans = [0]

for i in range(1, len(s)):
    if s[i] == 'a':
        ans[-1] = 1 - ans[-1]
        ans.append(1)
    else:
        ans.append(0)


print(' '.join([str(i) for i in ans]))

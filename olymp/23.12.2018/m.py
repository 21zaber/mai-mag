a, b, c, d = map(float, input().split())

from math import *

l = 64.517

#   z = l/(tan(c) + (tan(a) + tan(c))*(tan(d))/(tan(a) - tan(d)))
#
#   y = tan(d) * z / (tan(a) - tan(d))
#
#   h = (tan(b) + tan(a)) * y

k = l / (tan(c) + tan(d))

x = k * tan(d)

y = x / tan(b)

z = tan(a) * y

h = x + z

print(h)

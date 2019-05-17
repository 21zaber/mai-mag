import sys
import json
import subprocess
import shlex
from pprint import pprint



n = 100
step = n // 10

def conv(a):
    if a == 0:
        return ' 1'
    if a == 1:
        return '-1'
    if a == 2:
        return ' i'
    if a == 3:
        return '-i'
    

def call():
    global n
    cmd = './a.out '
    p = subprocess.Popen(shlex.split(cmd), stdout=subprocess.PIPE)
    out, err = p.communicate()

    s = out.decode()
    s = s.replace('\n', '')

    if not s:
        return None

    d = json.loads(s)

    d = tuple([tuple([conv(i) for i in j]) for j in d])

    return d

def print_v(v, start=' ', end=',', sep=', '):
    print('{start}{v}{end}'.format(start=start, end=end, v=sep.join(v)))

def print_mx(m):
    print_v(m[0], start='(')
    for i in m[1:-1]:
        print_v(i)
    print_v(m[-1], end=')')

mxs = set()

for i in range(n):
    if i % step == 0:
        print('[{}/{}]'.format(i, n), file=sys.stderr)
    m = call()
    if not m or m in mxs:
        continue

    print_mx(m)
    mxs.add(m)
    

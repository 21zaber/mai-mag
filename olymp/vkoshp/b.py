


l = []
ss = set()

while 1:
    s = input()
    for i in s.split('\\cite{')[1:]:
        n = i[:i.find('}')]
        if n not in ss:
            ss.add(n)
            l.append(n)

    if s.startswith('\\begin{thebibliography}{99}'):
        d = {}
        tpl = []
        txt = ''
        while 1:
            s = input()
            if s.startswith('\\end{thebibliography}'):
                break
            txt += s+'\n'

        for i in txt.split('\\bibitem{')[1:]:
            qw = '\\bibitem{'
 
            ttt = i.split('}', 1)
           #if len(ttt) == 1:
           #    k, v = ttt[0], '\n'
           #else:
            #print('"{}"'.format(i), ttt)
            k, v = ttt
            
            d[k] = v
            tpl.append((k, v))

        break

f = True

for i in range(len(l)):
    if l[i] != tpl[i][0]:
        f = False
        break

if f:
    print('Correct')
    exit(0)

print('Incorrect')
print('\\begin{thebibliography}{99}')
for i in l:
    print('\\bibitem{' + i + '}' + d[i],end='')
print('\\end{thebibliography}')


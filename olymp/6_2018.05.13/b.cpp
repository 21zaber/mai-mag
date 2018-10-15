#include <iostream>
#include <set>
#include <map>


using namespace std;

int get_3bits(long long a, int i){
    return (a >> i) & 7;
}

long long get_op(int i){
    return (1 << (i+1)) - (1 << i);
}

int main() {
    int n;
    cin >> n;
    map<long long, long long> d;
    d[0] = 1;
    set<long long> s;
    s.insert(0);

    long long bar = 0;
    for (int i = n - 1; i > 0; i-=2){
        bar += 1 << (i-1);
    }

    //cout << bar << endl;

    while (s.size() > 0){
        long long a = *s.begin();

        if (a >= bar) break;

        s.erase(s.begin());

        if (a % 4 == 0) {
            d[a+1] += d[a];
            s.insert(a+1);
            //cout << "op1: " << a << endl;
        }

        for (int i = 0; i < n-2; i++) {
            if (get_3bits(a, i) == 1) {
                long long b = a + get_op(i);
                d[b] += d[a];
                s.insert(b);
                //cout << "op2: " << a << ' ' << b << endl;
            }    
        }
    }

  //for (auto i = d.begin(); i != d.end(); ++i){
  //    cout << i->first << ' ' << i->second << endl;
  //}

    cout << d[bar] << endl;
}


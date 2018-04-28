#include <iostream>
#include <algorithm>

using namespace std;

typedef struct el{
    int l,r,v;
} el;

int main() {
    int n, k;
    long long p = 1;
    cin >> n >> k;

    long long t = pow(2, n-1);
    long long mx = t*2+1;
    cout << k << ' ' << mx-k << ' ';
    for (long long i = 0; i < t-1; ++i) {
        long long x = p;
        if (x == k or x == mx-k) {
            x++;
        }
        p = x+1;
        cout << x << ' ' << mx-x << ' ';
    }
    cout << endl;

    
}

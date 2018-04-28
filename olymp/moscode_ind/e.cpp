#include <iostream>

using namespace std;

typedef struct el{
    int l,r,v;
} el;

int main() {
    int n, k;
    long long p = 1;
    cin >> n >> k;

    cout << k << ' ' << n+1-k << ' ';
    long long t = pow(2, n);
    for (long long i = 0; i < t-1; ++i) {
        long long x = p;
        if (x == k or x == n+1-k) {
            x++;
        }
        p = x+1;
        cout << x << ' ' << n+1-x << ' ';
    }

    
}

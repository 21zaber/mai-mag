#include <bits/stdc++.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    while (a && b) {
        if (a) b %= a;
        if (b) a %= b;
    }
    return a | b;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
    int n, cs = 1;
    for(cin >> n; n; cin >> n) {
        int C[n];
        int64_t ans = 0;
        int r[6] = {0, 0, 0, 0, 0, 0};
        for(int &x: C) cin >> x;
        for(int i = n-2; i >= 0; --i) {
            ++r[C[i+1]];
            for(int x = C[i]+1; x < 6; ++x) {
                ans += (x-C[i])*(x-C[i])*r[x];
            }
        }
        cout << "Case #" << cs++ << ": The contest badness is ";
        ans *= 2ll;
        if (ans % int64_t(n*(n-1)) == 0)
            cout << ans / int64_t(n*(n-1));
        else { 
            int64_t d = gcd(ans, n*(n-1));
            cout << ans / d << '/' << (n*(n-1)) / d;
        }
        cout << ".\n";
    }
	return 0;
}

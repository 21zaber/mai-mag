#include <bits/stdc++.h>
#include <stdint.h>

using namespace std;

#define int64_t uint64_t

#define K 8
#define N 300100
///#define M (int64_t)2147483647
//#define M (int64_t)39916801
#define M (int64_t)524287
//#define M (int64_t) 100000000000000000
//#define M 1000000007

#define pp pair<int, int>

map<pp, int> mp;
int *im;

int64_t inverse(int64_t a, int64_t n)
{
    if (im[a] > 0)
        return im[a];

    int64_t tmp;
    int64_t t = 0, t1 = 1;
    int64_t r = n, r1 = a; 
    while (r1 != 0) {
        int64_t q = r / r1;
        tmp = t - q * t1; t = t1; t1 = tmp;
        tmp = r - q * r1; r = r1; r1 = tmp;
    }
    if (t < 0)
        t += n;
    t = (t + n) % n;
    im[a] = t;
    return t;
}

int64_t cnk(int64_t n, int64_t k){
    if (n < k) return 0;
    if (n == k) return 1;
    pp p = make_pair(n,k);

    if (mp.find(p) != mp.end())
        return mp[p];

    //int64_t a = (n * cnk(n-1, k) / (n-k)) % M;
    int64_t a = 1;

    for (int i = k+1; i <= n; ++i) {
        a *= i;
        a %= M;
        a *= inverse(i-k, M);
        a %= M;
    }

    mp[p] = a;
//    cout << "CNK: " << n << ' ' << k << " = " << a << endl;
    return a;
};

int main() {
    int n;
    cin >> n;
    int64_t *dp[2];
    for (int i = 0; i < 2; ++i) {
        dp[i] = (int64_t *)calloc(N+1, sizeof(int64_t));
    }
    im = (int *)calloc(N+1, sizeof(int));
    for (int i = 0; i < N; ++i) {
        im[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        dp[1][a]++;
    }

    if (dp[1][1]) {
        cout << 1 << endl;
        return 0;
    }
    for (int j = 1; j <= N; ++j) {
        int k = 1;
        dp[0][j] = 0;
        while (k * j < N) {
            dp[0][j] += dp[1][k*j];
            k++;
        }
        //if (dp[0][j]) cout << "DP: " << 0 << ' ' << j << " = " << dp[0][j] << endl;
    }

//  cout << "asd\n";
//  cout << cnk(0, 2) << endl;

    for (int i = 2; i < K; ++i) {
        for (int j = N-1; j > 0; --j) {
            int k = 2;
            dp[1][j] = cnk(dp[0][j], i) % M;

            while (j * k < N) {
                dp[1][j] = (dp[1][j] - dp[1][j* k] + M) % M;
                k++;
            }

//          if (dp[1][j]) cout << "DP: " << i << ' ' << j << " = " << dp[1][j] << endl;
        }
        if (dp[1][1]) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}

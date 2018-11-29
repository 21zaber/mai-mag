#include <bits/stdc++.h>

using namespace std;


vector<int64_t> ph;
int64_t n;

int64_t sum(int a) {
    int64_t res= 0, r = a;
    for (; r >= 0; r = (r & (r+1)) -1) {
        res += ph[r];
    }

    //cout << "Sum: " << a << ' ' << res << endl;
    return res;
}

int inc(int i, int64_t d) {
    for (; i < n; i = (i | (i+1)))
        ph[i] += d;
    return 1;
}

int get_min(int64_t t) {
    int l = 0, r = n;
    while (l < r) {
//        cout << l << ' ' << r << endl;
        int m = l + (r-l) / 2;
        if (t < sum(m))
            r = m;
        else
            l = m+1;
    }

    return r;    
}

int main () {
    int64_t t;
    cin >> n >> t;

    ph.assign(n+1, 0);

    int64_t a[n];
    int64_t mn = 1000000000;
    for (int i =0; i <n; ++i) {
        cin >> a[i];
        inc(i, a[i]);
        mn = min(mn, a[i]);
    }

    int64_t csum = sum(n-1), cn = n, ans = 0;

    while (t >= mn && t > 0) {
//        cout << ans << ' ' << csum << ' ' << t << endl;
        while (t < csum) {
            int cmn = get_min(t);
//            cout << "Del: " << cmn << endl;
            inc(cmn, -a[cmn]);
            csum -= a[cmn];
            a[cmn] = 0;
            cn--;
            if (!cn) break;
        }
        if (!cn) break;

        ans += cn * (t / csum);
        t %= csum;
    }

    cout << ans << endl;
}

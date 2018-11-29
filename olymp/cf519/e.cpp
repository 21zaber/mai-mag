#include <bits/stdc++.h>

using namespace std;

int main() {

    int n, m;
    cin >> n >> m;

    int64_t a[n], b[n], ans[n], as[n], bs[n];
    vector<pair<int, int> > ppl;
    for (int i = 0; i < n; ++i) { 
        cin >> a[i] >> b[i];
        ans[i] = 0;
        ppl.push_back(make_pair(a[i]-b[i], i));
    }

    for (int i = 0; i < m; ++i) {
        int v, u, d;
        cin >> u >> v;

        d = min(a[u-1] + b[v-1], a[v-1] + b[u-1]);
        ans[u-1] -= d;
        ans[v-1] -= d;
    }

    sort(ppl.begin(), ppl.end());

    for (int i = 0; i < n; ++i){
        int p = ppl[i].second;
        as[i] = a[p];
        if (i) as[i] += as[i-1];
        bs[i] = b[p];
        if (i) bs[i] += bs[i-1];
    }

//  for (int i = 0; i < n; ++i) {
//      int p = ppl[i].second;
//      cout << ppl[i].first << ' ' << p << ' ' << as[i] << ' ' << bs[i] << ' ' << ans[p] << endl;
//  }

    for (int i = 0; i < n; ++i) {
        int p = ppl[i].second;
//        cout << "i: " << i;
        if (i) {
//            printf(" left: %d * %d + %d ", b[p], i, as[i-1]);
            ans[p] += b[p] * i + as[i-1];
        }
        if (i < n-1) {
//            printf(" right: %d * %d + %d - %d ", a[p], (n - i - 1), bs[n-1], bs[i]);
            ans[p] += a[p] * (n - i - 1) + bs[n-1] - bs[i];
        }
//        cout << endl;
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}

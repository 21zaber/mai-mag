#include <bits/stdc++.h>
using namespace std;


vector<int> w;
vector<map<int, int> > m;

vector<int64_t> mw1, mw2;

int64_t dfs(int v, int p) {
    mw1[v] = w[v];
    mw2[v] = w[v];

    int64_t m1 = -1, m2 = -1;

    for (auto i = m[v].begin(); i != m[v].end(); ++i) {
        if (i->first == p) continue; 

        int64_t t = dfs(i->first, v);
        mw1[v] = max(mw1[v], t);
      //if (mw1[i->first]  > mw1[v]) 
      //    mw1[v] = mw1[i->first];
      //if (mw2[i->first] > mw1[v])
      //    mw1[v] = mw2[i->first];

        if (mw2[i->first] - i->second > m1) {
            m2 = m1;
            m1 = mw2[i->first] - i->second;
        } else if (mw2[i->first] - i->second > m2) {
            m2 = mw2[i->first] - i->second;
        }
    }

    mw1[v] = max(mw1[v], m1+m2+w[v]);
    mw2[v] = max(mw2[v], w[v] + m1);
    mw1[v] = max(mw1[v], mw2[v]);
    return max(mw1[v], mw2[v]);
}

int main() {
    int n;
    cin >> n;
    w.resize(n);
    mw2.resize(n, 0);
    mw1.resize(n, 0);
    m.resize(n);
    for (int i=0; i < n; ++i) cin >> w[i];

    for (int i = 1; i < n; ++i) {
        int x, y, z;
        cin >>x >> y >> z;

        m[x-1][y-1] = z;
        m[y-1][x-1] = z;
    }

    int64_t ans = 0;
    dfs(0, -1);

    for (int i = 0; i < n; ++i) {
        ans = max(ans, mw1[i]);
//        cout << mw1[i] << ' ';
    }
//      cout << endl;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, mw2[i]);
//          cout << mw2[i] << ' ';
    }
//      cout << endl;

    cout << ans << endl;


}

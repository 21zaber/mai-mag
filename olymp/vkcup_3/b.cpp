#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

typedef struct elem {
    int l, r, v;
} elem;

int cmp(elem a, elem b) {
    return (a.l < b.l) || (a.l == b.l && a.r < b.r);
}

int main() {
    ll n, a = 0;
    cin >> n;
    vector<ll> t(n+1, 0), ans(n, 0);
    vector<elem> v(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> a;
        v[i].l = i, v[i].r = 0, v[i].v = a;
    }
    a = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i];
        a += t[i];
        t[i] = a;
    }

    for (int i = 0; i < n; ++i) {
        v[i].r = lower_bound(t.begin(), t.end(), t[i] + v[i].v) - t.begin()-1;
    }

    //sort(v.begin(), v.end(), cmp);
  //for (int i =0; i <= n; ++i) cout << t[i] << ' ';
  //cout << endl;
  //
  //
  //for (int i =0; i < n; ++i) cout << v[i].l << ' ' << v[i].r << ' ' << v[i].v << endl;
  //cout << endl;
    multimap<int, pair<int, int> > mp;
    for (int i = 0; i < n; ++i) {
        a = 0;
        if (v[i].v > 0)
            mp.insert(make_pair(v[i].r, make_pair(v[i].l, v[i].v)));
        for (auto j = mp.begin(); j != mp.end(); ++j) {
            if (j->first <= i) {
                a += (t[i+1] - t[i]) - ((t[i+1] - t[j->second.first]) - j->second.second);
                //cout << t[i+1] << ' ' << t[j->second.first] << ' ' << j->second.second << endl;
            } else {
                break;
            }
        }
        mp.erase(i);
        ans[i] = a + (mp.size()) * (t[i+1] - t[i]);
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << endl;
}

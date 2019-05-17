#include <bits/stdc++.h>

using namespace std;

vector<vector <int> > v;

int main() {
    int n, m;
    cin >> n >> m;

    v.resize(n);

    for (int i = 0; i < m; ++i) {
        int a,b;
        cin >>a >>b;
        v[a-1].push_back(b-1);
        v[b-1].push_back(a-1);
    }

  //if (n == 1) {
  //    cout << "NO\n";
  //    return 0;
  //}

    int p1=-1, p2=-1;

    for (int i = 0; i < n; ++i) {
        if (v[i].size() < n-1) {
            p1 = i;
            break;
        }
    }

    if  (p1 < 0) {
        cout << "NO\n";
        return 0;
    }

    int j = 0;
    sort(v[p1].begin(), v[p1].end());
    for (int i = 0; i < n; ++i){
        if (j < v[p1].size() && i == v[p1][j]) {
            ++j;
            continue;
        }
        if (i != p1){
            p2 = i;
            break;
        }
    }
    if  (p2 < 0) {
        cout << "NO\n";
        return 0;
    }

  //cout << p1 << ' ' << p2<<endl;

    vector<int> st(2);
    vector<int> way(n, -1);
    st[0] = p1;
    st[1] = p2;
    way[p1] = 0;
    way[p2] = 0;
    int l = 0;

    while (l < st.size()) {
        int cv = st[l++];

        for (int i = 0; i< v[cv].size(); ++i){
            int tov = v[cv][i];
            if (way[tov] < 0) {
                way[tov] = way[cv] + 1;
                st.push_back(tov);
            }
        }
    }
    for (int i = 0; i < n; ++i) 
        if (way[i] < 0) way[i] = n;

  //for (int i = 0; i < n; ++i) cout << way[i] << ' ';
  //cout << endl;

    vector<pair <int, int> > pairs;

    for (int i = 0; i < n; ++i) {
        pairs.push_back(make_pair(way[i], i));
    }

    sort(pairs.begin(), pairs.end());

    vector<int> ans(n);

    for (int i = 0; i < n; ++i) {
        ans[pairs[i].second] = i+1;
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << "\n"; ans[p1] = 1; ans[p2] = 1;
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << "\n"; 


}

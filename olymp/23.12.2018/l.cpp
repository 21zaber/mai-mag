#include <bits/stdc++.h>

using namespace std;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >>m;

    int a[n];

    for (int i=0; i < n; ++i) cin >> a[i];

    vector<set<int> > b(n), sb(2);
    

    for (int i = 0; i < m; ++i) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        if (a[x] != a[y]) {
            b[x].insert(y);
            b[y].insert(x);
            sb[a[x]].insert(y);
            sb[a[y]].insert(x);
        }
    }


    int c[2];
    c[0]=0;c[1]=0;
    for (int i = 0; i < n; ++i) {
        c[a[i]]++;
    }

    for (int i = 0; i < n; ++i) {
        int ans = 0;
        int color = a[i];

        // same color
        ans += c[color]-1;

        // public road
        ans += b[i].size();

        // public road from same color
      //vector<int> diff;
      //set_difference(sb[color].begin(), sb[color].end(), b[i].begin(), b[i].end(), inserter(diff, diff.begin()));
      //ans += diff.size() * 2;
        ans += (sb[color].size() - b[i].size()) * 2;

        int k = 3;
        if (b[i].size()) k -= 1;

        ans += (c[1-color] - sb[color].size()) * k;

        cout << ans << ' ';
    }
    cout << endl;




};

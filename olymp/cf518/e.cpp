#include <bits/stdc++.h>

using namespace std;

vector< vector<int> > m;

vector<int> ln;

int dfs(int v, int p) {

    ln[v] = ln[p] +1;

    for (int i = 0; i < m[v].size(); ++i) {
        if (m[v][i] != p) {
            dfs(m[v][i], v);
        }
    }
} 

int main() {
    int n, k;
    cin >> n >> k;

    m.resize(n);
    ln.resize(n);


    for (int i = 0; i < n-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        m[a-1].push_back(b-1);
        m[b-1].push_back(a-1);
    }

    int v = n-1, u = n-1;
    dfs(v, -1);
    for( int i = 0; i < n; ++i) {
        if (ln[i] > ln[v]) v = i;
    }
    ln.resize(n,0);

    dfs(v, -1);
    for( int i = 0; i < n; ++i) {
        if (ln[i] > ln[u]) u = i;
    }





}

#include <bits/c++.h>

int main(){
    int n,m,k;
    cin >> n >> m >> k;
    int c[n];
    for (int i = 0; i < n; ++i) cin >> c[i];

    vector<vector<int> > e(n, vector<int>());


    for (int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        e[a-1].push_back(b-1);
        e[b-1].push_back(a-1);
    }

    set<int> lc;
    for (int i = 0; i< n; ++i) {
        lc.clear();
        lc.insert(c[i]);
        for (auto j = e[i].begin(); j != e[i].end(); ++ j){
            lc.insert(c[*j]);
        }

        if (lz.size() < k) {
            cout << "1\n";
            return 
        }
        
    }



}



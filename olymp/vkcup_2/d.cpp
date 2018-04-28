#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, a, b;
    cin >> n >> a >> b;
    a--, b--;
    vector<int> g(n-1), k(n);
    for (int i = 0; i < g.size(); ++i){
        cin >> g[i];
    }
    for (int i = 0; i < k.size(); ++i){
        cin >> k[i];
    }

    map<int, pair<int, int> > keys;

    int l = a, r = a;
    
    keys[k[a]] = make_pair(a, a);
    vector<long long> way(n, -1);
    way[a] = 0;

    for (int i = 0; i < n; ++i){
        int nl = l-1;
        int nr = r+1;
        if (nl >= 0){
            if (keys.find(g[nl]) != keys.end()){
                pair<int, int> tmp = keys[g[nl]];
                int fr;
                if (tmp.second > -1) fr = tmp.second;
                if (tmp.first > -1) fr = tmp.first;

                way[nl] = way[fr] + abs(fr - nl);
                if (keys.find(k[nl]) == keys.end()) {
                    // key doesnt exist
                    keys[k[nl]] = make_pair(nl, nl);
                    l = nl;
                    continue;
                }
                //  left key doesnt exist or our way are better
              //if (keys[k[nl]].first < 0 || way[keys[k[nl]].first] + abs(keys[k[nl]].first - nl) >= way[nl]){
              //    keys[k[nl]].first = nl;
              //}
                keys[k[nl]].first = nl;
                if (keys[k[nl]].second < 0 || keys[k[nl]].second < nl){
                    keys[k[nl]].second = nl;
                }
                
                l = nl;
                continue;
            } 
        }   
        if (nr < n){
            if (keys.find(g[nr-1]) != keys.end()){
                pair<int, int> tmp = keys[g[nr-1]];
                int fr;
                if (tmp.first > -1) fr = tmp.first;
                if (tmp.second > -1) fr = tmp.second;

                way[nr] = way[fr] + abs(fr - nr);
                if (keys.find(k[nr]) == keys.end()) {
                    // key doesnt exist
                    keys[k[nr]] = make_pair(nr, nr);
                    r = nr;
                    continue;
                }
                //  rignt key doesnt exist or our way are better
              //if (keys[k[nr]].second < 0 || way[keys[k[nr]].second] + abs(keys[k[nr]].second - nr) >= way[nr]){
              //    keys[k[nr]].second = nr;
              //}
                keys[k[nr]].second = nr;
                if (keys[k[nr]].first < 0 || keys[k[nr]].first > nr){
                    keys[k[nr]].first = nr;
                }
                r = nr;
                continue;
            }
        }
        break;
    }    
    cout << way[b] << endl;
    return 0;
}

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


bool check(set<int> a, set<int> b){
    auto ai = a.begin();
    auto bi = b.begin();

    while (ai != a.end() && bi != b.end()) {
        if (*ai == *bi) return 1;
        if (*ai < *bi) {
            ++ai;
            continue;
        }
        ++bi;
    }
    return 0;
}

int main() {
    int n, k, m;
    cin >> n >> k >>m;

    map<int, int> kmp;
    map<int, set<int> > u;
    vector<int> v;

    for (int i =0; i < n; ++i){
        kmp[i] = i;
        u[i] = set<int>();
    }

    for (int i = 0; i < k; ++i){
        int x, y;
        cin >> x>>y;
        x--;
        y--;
        u[x].insert(y);
        u[y].insert(x);
    }

    for (int i = 0 ; i < m ; ++i){
        int x, y;
        cin >> x>>y;
        x--;
        y--;

        if (y < x) {
            int t = x;
            x = y;
            y = t;
        }

        int kx = kmp[x], ky = kmp[y];

        if (!(u[kx].find(ky) != u[kx].end() || u[ky].find(kx) != u[kx].end()))
{
            v.push_back(i+1);

            kmp[y] = kx;
            u[kx].insert(u[ky].begin(), u[ky].end());
        }        
    }

    cout << v.size() << endl;
    for (int i = 0; i < v.size(); ++i){
        cout << v[i] << ' ';
    }
    cout << endl;

}

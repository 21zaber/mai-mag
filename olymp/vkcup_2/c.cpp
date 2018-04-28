#include <vector>
#include <iostream>
#include <algorithm>
#include <set>


using namespace std;


long long C(long long n, long long k){
    //cout << n << ' ' << k << endl;
    if (k == 0 || n < k) return 0;
    if (k == 1) return n;
    if (k == 2) return (n * (n-1)) / 2;
    if (k == 3) return (n * (n-1) * (n-2)) / 6;
    return 0;
}

int main() {
    int g, d, f;
    set<int> gs, ds, fs;
    vector<int> all;
    
    cin >> g >> d >> f;

    int t;
    for (int i = 0; i < g; ++i) {
        cin >> t;
        gs.insert(t);
        all.push_back(t);
    }
    for (int i = 0; i < d; ++i) {
        cin >> t;
        ds.insert(t);
        all.push_back(t);
    }
    for (int i = 0; i < f; ++i) {
        cin >> t;
        fs.insert(t);
        all.push_back(t);
    }

    sort(all.begin(), all.end());

    int n = all.size();

  //for (int i = 0; i < n; i++) cout << all[i] << ' ';
  //cout << endl;

    long long ans = 0;
    int gn, dn, fn;
    int l, r;
    int gk, dk, fk;

    for (int li = 0; li < n; ++li) {
        for (int ri = li+1; ri < n; ++ri) {
            l = all[li], r = all[ri];
            if (l * 2 < r) break;
            gn = 1, dn = 2, fn = 3;
            if (gs.find(l) != gs.end()) gn--;
            if (gs.find(r) != gs.end()) gn--;
            if (ds.find(l) != ds.end()) dn--;
            if (ds.find(r) != ds.end()) dn--;
            if (fs.find(l) != fs.end()) fn--;
            if (fs.find(r) != fs.end()) fn--;

            if (gn < 0) break;

            auto gli = gs.upper_bound(l);
            auto gri = gs.lower_bound(r);
            auto dli = ds.upper_bound(l);
            auto dri = ds.lower_bound(r);
            auto fli = fs.upper_bound(l);
            auto fri = fs.lower_bound(r);
          //cout <<*gli << " " << l << endl;
          //cout <<*gri << " " << r << endl;
          //cout <<*dli << " " << l << endl;
          //cout <<*dri << " " << r << endl;
          //cout <<*fli << " " << l << endl;
          //cout <<*fri << " " << r << endl;
            gk = 0, dk = 0, fk = 0;

  //        if (dli == ds.end()) cout << "*" << endl;
  //for (auto i = dli; i != dri; ++i) cout << *i << ' ';
  //cout  << "#" << endl;

            for (auto i = gli; i != gri; ++i) gk++;
            for (auto i = dli; i != dri; ++i) dk++;
            for (auto i = fli; i != fri; ++i) fk++;

            long long t = C(gk, gn) * C(dk, dn) * C(fk, fn); 
          //cout << t << " " << gk << " " << gn << " " << dk << " " << dn << " " << fk << " " << fn << endl;
            ans += t;
        }
    }

  //for (auto i = gs.begin(); i != gs.end(); ++i) cout << *i << ' ';
  //cout << endl;
  //for (auto i = ds.begin(); i != ds.end(); ++i) cout << *i << ' ';
  //cout << endl;
  //for (auto i = fs.begin(); i != fs.end(); ++i) cout << *i << ' ';
  //cout << endl;

    cout << ans << endl;
}

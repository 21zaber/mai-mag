#include <vector>
#include <iostream>
#include <string>

#define FAIL -100

using namespace std;

vector<int> m[30];


int lbsearch(int k, vector<int> &v) {

    int m;
    int l = 0, r = v.size()-1;

    while (l<r) {
        m = l + (r-l) / 2;
        if (k
        if (k <= v[m]) {
            r = m;
        } else if (k > v[m]) {
            l = m;
        }
        cout << l << ' ' << r << endl;
    }
    return v[l];
}

int main(){
    string s;
    cin >> s;

    int n = s.length();

    for (int i = 'a'; i <= 'z'; ++i){
        m[i] = vector<int>();
    }

    for (int i = 0; i < n; ++i){
        m[s[i]].push_back(i);
    }

    for (int i = 'a'; i <= 'z'; ++i){
        cout << i << ": ";
        for (int j = 0; j < m[i].size(); ++j) cout << m[i][j] << ' ';
        cout << endl;
    }

    int ans = 0;



    for (int i = n-1; i > 0; --i, ++ans){
        cout << "i: " << i << endl;
        int mx_l = 0;
        for (int l = 1; l <= i/2 + i%2; ++l) {
            cout << "l: " << l << endl;
            int p = i-l;
            for (int j = 0; j < l; ++j) {
                int sym = s[i-j];
                int t = lbsearch(p, m[sym]);
                cout << "lbsearch: " << p << " = " << t << endl;
                if (t == -1) {
                    p = FAIL;
                    break;
                }
                p = t-1;
            }
            if (p == FAIL) break;
            mx_l = l;
        }
        if (mx_l > 1) i -= mx_l - 1;
        cout << mx_l << endl;
    }

  //int t = lbsearch(3, m['s']);
    cout << ans+1 << endl;
}

#include <bits/stdc++.h>

using namespace std;

int main() {

    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<int> idx(n);
    for(int i = 0; i < n; ++i) {
        cin >> idx[i];
        idx[i]--;
    }


    int last = 0, cur = 0;

    map<int, int> d;
    string ca = "";

    for (int i = 0; i < s.size(); ++i){

        if ( i == idx[cur]){
cout << ca << s[i];
            ca = "";
            d.clear();
            ++cur;
            continue;
        }

 //       cout << s[i]  << ": ";
        if (s[i] < s[idx[cur]]) {
            if (ca.empty() or s[i] < ca[0]) {
//                cout << "0\n";
                d.clear();
                d[s[i]] = 0;
                ca = s[i];
            } else if (d.count(s[i])) {
//                cout << "2\n";
                for (int k = d[s[i]]; k < ca.size(); ++k)
                    d.erase(ca[k]);

//                cout << ca << ' ' << d[s[i]]+1 << endl;
                ca = ca.substr(0, d[s[i]]+1) + s[i];
                d[s[i]] = ca.size()-1;
            } else {
//                cout << "3\n";
                int p = ca.size();
                for (int k = ca.size()-1; k > 0; --k) {
                    if (ca[k] > s[i]){
                        if (d.count(ca[k]))
                            d.erase(ca[k]);
                    } else
                        break;
                    p--;
                }
                ca = ca.substr(0, p) + s[i];
                d[s[i]] = ca.size()-1;
            }

        }
//cout << '!' << ca << endl;
    }

    cout << endl;
}

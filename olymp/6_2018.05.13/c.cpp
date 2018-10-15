#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<double> v;
    for (int i = 0; i < n; ++i){
        double a;
        cin >> a;
        v.push_back(a);
        v.push_back(a+360);
    }

    sort(v.begin(), v.end());

    //for (int i= 0 ;i < v.size();i++) cout << v[i] << ' ';

    if (n < 2) {
        cout << "0\n";
        return 0;
    }
    int l = 0, r = 1, ans = 0;
    while (r < n and l < n) {
        double d = v[r] - v[l];
        if (fabs(d - 180) < 0.0001){
            ans += n-2;
            l++;
            r++;
            continue;
        }
        if (d < 180) {r++; continue;}
        if (d > 180) {l++; continue;}
    }

    cout << ans << endl;
}

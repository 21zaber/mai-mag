#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int f(int a) {
    int ans = 1;

    while (a % 2 == 0) {
        a/=2;
        ans = 2;
    }

    //int mx = 1 + sqrt(a);
    for (int i = 3; i*i <= a; i+=2){
        while (a % i == 0) {
            a /= i;
            ans = max(ans, i);
        }
    }
    if (a > 1) {
        ans = a;
    }
    return ans;
}

int main() {
    int x;
    cin >> x;
    vector<int> v; 
    int t = f(x);

    //cout << t << endl;

    for (int i = 1; i < t;++i) v.push_back(x-i);

    int ans = x;

    for (auto j : v) {
        int tmp = f(j);
        if (tmp != j) {
            //cout << j << ' ' << tmp << endl;
            ans = min(ans, j - tmp + 1);
        } else {
            ans = min(ans, j);
        }
    }
    cout << ans << endl;


}

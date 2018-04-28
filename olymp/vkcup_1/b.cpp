#include <vector>
#include <iostream>

int min(int a, int b) {
    return a < b ? a : b; 
}

int max(int a, int b) {
    return a > b ? a : b; 
}

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> ans;

    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;

        int a = 1 + (k - max(1, i-k)) + (min(n, i+k) - k);
        //cout << a << endl;

        if (t) {
            a += ans[t-1];
            if (t + k >= i - k) {
                a -= min(t + k, n) - max(1, i - k) + 1;
                //cout << a << " " << min(t + k, n) << " "  << max(1, i - k) << endl;
            }
        }
        ans.push_back(a);
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    cout << endl;
}

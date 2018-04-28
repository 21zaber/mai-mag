#include <iostream>
//#include <stdlib>

using namespace std;


int main() {
    int n, k;
    cin >> n >> k;
    int *a = (int *)calloc(n, sizeof(int)), *b = (int *) calloc(k, sizeof(int));

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < k; ++i) {
        cin >> b[i];
        b[i]--;
    }

    int ans = 0;

    for (int i = 0; i < n-k+1; ++i) {
        ans++;
        for (int j = k-2; j >= 0; --j) {
            if (a[i + b[j]] > a[i + b[j+1]]) {
                ans--;
                break;
            }
        }
    }
    cout << ans << endl;
}

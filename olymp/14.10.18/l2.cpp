#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    map<int, pair<int, int> > cache;
    cin >> n;
    int A[n], JMP[n];
    for(int &x: A) cin >> x;
    JMP[n-2] = JMP[n-1] = n-1;
    for(int i = n-3; i >= 0; --i) {
        if (!!(A[i] > A[i+1]) == !!(A[i+1] > A[i+2]))
            JMP[i] = JMP[i+1];
        else
            JMP[i] = i+1;
    }
#ifdef EBUG
    for(int i = 0; i < n; ++i) {
        cout << setw(4) << i;
    }
    cout << endl;
    for(int i = 0; i < n; ++i) {
        cout << setw(4) << A[i];
    }
    cout << endl;
    for(int i = 0; i < n; ++i) {
        cout << setw(4) << JMP[i];
    }
    cout << endl;
#endif
    int minrun, q;
    for(cin >> q; q --> 0; ) {
        cin >> minrun;
        if (cache.count(minrun)) {
            cout << cache[minrun].first << ' ' << cache[minrun].second << '\n';
            continue;
        }
        pair<int, int> ans;
        for(int i = 0; i < n; ) {
            ++ans.first;
            if (JMP[i] - i + 1 >= minrun) {
                i = JMP[i] + 1;
            }
            else {
                ans.second += min(minrun, n - i) - JMP[i] + i - 1;
                i = min(n, i + minrun);
            }
        }
        cout << ans.first << ' ' << ans.second << '\n';
        cache[minrun] = ans;
    }
    return 0;
}


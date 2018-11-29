#include <bits/stdc++.h>

using namespace std;

int32_t a[100100], b[100100], rb[100100], d[100100], c[100100];

int main() {
    int32_t n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]); 
        c[i] = 0;
    }

    for (int k = 1; k < m; ++k){

        for (int i = 0; i < n; ++i) {
            scanf("%d", &b[i]); 
            rb[b[i]] = i;
            d[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            b[i] = rb[a[i]];
        }

        for(int i = 1, p = 0, o = c[0]; i < n; ++i) {
            if (b[i] != b[i-1]+1 || o != c[i]) {
                o = c[i];
                c[i] = ++p;
            } else {
                c[i] = p;
            }   
        }

//      for(int i = 0, p = 0; i < n-1; ++i) {
//          if (b[i] != b[i+1]+1){
//              c[i+1] = ++p;
//          } else {
//              //p = c[i] = max(p, c[i]);
//              c[i] = p;
//          }
//      }
//   for (int i = 0; i < n; ++i) cout << b[i] << ' ';
//   cout << endl;
//   for (int i = 0; i < n; ++i) cout << c[i] << ' ';
//   cout << endl;
    }


    int64_t ans = 0, l = 1;

    for (int i = 1; i < n; ++i) {
        if (c[i] != c[i-1]){
            ans += (l * (l+1))/2;
            l = 0;
        }
        l++;
    }
    ans += (l * (l+1))/2;

    cout << ans << endl;
    return 0;
}




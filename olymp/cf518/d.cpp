#include <bits/stdc++.h>

using namespace std;

#define M 998244353
#define B 201

int main() {
    int n;
    cin >> n;

    int a[n+2];

    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i+1]);
    }
    a[0] = 1;
    a[n+1] = 1;
    n += 2;

    int64_t *dp[2][B], ps[2][B];
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < B; ++j) {
            dp[i][j] = (int64_t *)calloc(n, sizeof(int64_t));
            ps[i][j] = 0;
        }
    }

    dp[0][1][0] = 1;
    ps[0][0] = dp[0][0][0];
    ps[1][0] = dp[1][0][0];
    for (int j = 1; j < B; ++j) {
        ps[0][j] = ps[0][j-1] + dp[0][j][0];
        ps[1][j] = ps[1][j-1] + dp[1][j][0];
        ps[0][j] %= M;
        ps[1][j] %= M;
    }

    for (int i = 1; i < n; ++i) {
        if (a[i] == -1) {
            for (int j = 1; j < B; ++j) {
                dp[0][j][i] = ps[1][j-1] + ps[0][j-1];
              //for (int k = 1; k < j; ++k) {
              //    dp[0][j][i] += dp[1][k][i-1] + dp[0][k][i-1];
              //}
                dp[0][j][i] %= M;

                dp[1][j][i] = dp[0][j][i-1] + ((ps[1][B-1]-ps[1][j-1]+M) % M);
              //for (int k = j; k < B; ++k) {
              //    dp[1][j][i] += dp[1][k][i-1];
              //}

                dp[1][j][i] %= M;
            } 
        } else {
            dp[1][a[i]][i] = dp[0][a[i]][i-1];
            for (int j = a[i]; j < B; ++j) {
                dp[1][a[i]][i] += dp[1][j][i-1];    
                dp[1][a[i]][i] %= M;
            }

            dp[0][a[i]][i] = 0;
            for (int j = 1; j < a[i]; ++j) {
                dp[0][a[i]][i] += dp[0][j][i-1] + dp[1][j][i-1];    
                dp[0][a[i]][i] %= M;
            }
        }
        ps[0][0] = dp[0][0][i];
        ps[1][0] = dp[1][0][i];
        for (int j = 1; j < B; ++j) {
            ps[0][j] = ps[0][j-1] + dp[0][j][i];
            ps[1][j] = ps[1][j-1] + dp[1][j][i];
            ps[0][j] %= M;
            ps[1][j] %= M;
        }

      //for (int j = 0; j < 11; ++j){
      //    cout << ps[0][j] << ' ';
      //} cout << endl;
    }

  //for (int i = 1; i < 11; ++i) {
  //    printf("%d: ", i);
  //    for (int j = 0; j < n; ++j) {
  //        printf("(%d; %d) ", dp[0][i][j], dp[1][i][j]);
  //    }
  //    cout << endl;
  //}



    int64_t ans = 0;

    for (int i = 1; i < B; ++i) {
        ans += dp[0][i][n-1];
        ans %= M;
        ans += dp[1][i][n-1];
        ans %= M;
    }

    cout << ans << endl;

}

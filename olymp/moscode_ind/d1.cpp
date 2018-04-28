#include <iostream>
//#include <stdlib>

using namespace std;


int main() {
    int n, k, skip = 1;
    cin >> n >> k;
    int *a = (int *)calloc(n, sizeof(int)), *b = (int *) calloc(k, sizeof(int));
    int *p = (int *)calloc(k, sizeof(int));

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < k; ++i) {
        cin >> b[i];
        b[i]--;
        p[b[i]] = i;

        if (i > 1 && ((b[i] < b[i-1]) == (b[1] < b[0]))) skip = 0;

    }

    int ans = 0, s=1, step=1, t;

    for (int shft = 1; shft < k-1; ++shft) {
        t = 0;
        for (int i=0; i < k-shft-1; ++i) {
//            cout << shft+i << ' ' << shft+i+1 << ' ' << i << endl;
            if ((p[shft+i] > p[shft+i+1]) != (p[i] > p[i+1])){
                t = 1;
                break;
            }
        }
        if (t == 1) {
            step++;
            continue;
        }
        break;
    }

//    cout << "step: " << step << endl;

    int f = 0, start = 0;

    for (int i = 0; i < n-k+1; i+=s) {
   //     cout << "i: " << i << endl;
        ans++;
        s = step;
        //for (int j = k-2; j >= 0; --j) {
        if (f && skip) {
            start = k-2;
        } else {
            start = 0;
        }
        f = 1;
        for (int j = start; j < k-1; ++j) {
            if (a[i + b[j]] > a[i + b[j+1]]) {
  //              cout << i + b[j] << ' ' << i + b[j+1] << ' ' << j << endl;
                ans--;
                s = 1;
                f = 0;
                break;
            }
        }
    }
    cout << ans << endl;
}



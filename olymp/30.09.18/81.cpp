#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct elem_s {
    int c;
    int m;
    int p;
} elem;

double mabs(double a){
    if (a > 0) return a;
    return -a;
}          

bool cmp(elem a, elem b){
    double ac = (double)a.m / a.c;
    double bc = (double)b.m / b.c;
    return ac < bc;
}



int main() {
    int n, m, t;
    double s;
    cin >> t;
    cout.precision(13);
    for (int q = 0; q < t; ++q){
        cin >> n >> m >> s;

        vector<elem> kk(n), k;
        for (int i = 0; i < n; ++i) kk[i].c = 0;

        for (int i = 0; i < m; ++i){
            int x;
            cin >> x;
            kk[x-1].c++;
        }

        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            kk[i].m = x;
            kk[i].p = y;
            if (kk[i].c != 0) {
                k.push_back(kk[i]);
            }
        }

        sort(k.begin(), k.end(), cmp);

      //for (int i = 0; i < k.size(); ++i){
      //    cout << k[i].m << ' ' << k[i].p << ' ' << k[i].c  << endl;
      //}
      //cout << endl;

        double ans = (double)k[0].m / k[0].c;
        double mk = 0;//k[0].p * k[0].c;
        //cout << mk << endl;

        for (int i = 0; i < k.size()-1; ++i) {
            mk += k[i].p * k[i].c;
            double next = (double)k[i+1].m / k[i+1].c;
      //      cout << mk << ' ' << s << ' ' << next << ' ' << ans << endl;
            if (s < (next - ans) * mk){
                ans += s / mk;
                s = 0.0;
                break;
            }
            s -= (next - ans) * mk;
            ans = next;
        }

        if (s > 0.0000000000001) {
            mk += k[k.size()-1].p * k[k.size()-1].c;
            //cout << mk << ' ' << s << ' ' << ans << endl;
            ans += s / mk;
        }
        
        cout << ans << endl;
    }
}

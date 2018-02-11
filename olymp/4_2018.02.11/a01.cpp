#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

long long INF = 1000000000;

vector<int> ps, qs;
int n, p, q,tn,s;
int *seq, *u, *sl;

long long ans(int i, int ip, int iq) {
    if (i >= tn) return 0;

    int pl = seq[i]-1;

    if (pl < n) {
        int a = -INF, b = -INF;
        if (sl[pl] < s){
            sl[pl] += 1;
            a = ps[ip] + ans(i+1, ip+1, iq);
            sl[pl] -= 1;
        }
        if (u[pl] == 0) {
            u[pl] = 1;
            b = qs[iq] + ans(i+1, ip, iq+1);
            u[pl] = 0;
        }

        if (a > b)
            return a;
        else
            return b;
    } else {
        int a = INF, b = INF;
        if (sl[pl] < s){
            sl[pl] += 1;
            a = -ps[ip] + ans(i+1, ip+1, iq);
            sl[pl] -= 1;
        }
        if (u[pl] == 0){
            u[pl] = 1;
            b = -qs[iq] + ans(i+1, ip, iq+1);
            u[pl] = 0;
        }
        if (a < b) 
            return a;
        else
            return b;

    }

}


int main() {
    cin >> n >> s;
    tn = n * (s+1) * 2;

    //cout << tn << endl;

    seq = new int[tn];
    u = new int[2*n];
    sl = new int[2*n];

    for (int i = 0; i < 2*n; ++i) u[i]=0;
    for (int i = 0; i < 2*n; ++i) sl[i]=0;

    for (int i = 0; i < tn; ++i) cin >> seq[i];
    cin >> p;

    for (int i = 0; i < p; ++i) {
        int t;
        cin >> t;
        ps.push_back(t);
    }
    //cout  << p << ' '<< bps.size() << endl;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        qs.push_back(t);
    }
    //cout  << q << ' '<< bqs.size() << endl;

    sort(qs.rbegin(), qs.rend());
    sort(ps.rbegin(), ps.rend());
    cout << ans(0,0,0) << endl;
}

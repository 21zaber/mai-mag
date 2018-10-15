#include <iostream>
#include <vector>


using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> m(n), segs;

    for (int i = 0; i < n; ++i) cin >> m[i];


    int len = 1, d = -1;
    for (int i = 1; i < n; ++i){
        int nd = m[i] < m[i-1];
        if (d == -1 || nd == d){
            len++;
        } else {
            segs.push_back(len);
            len = 1;    
        }
        d = nd;
    }
    segs.push_back(len);

    for (int i = 0;i < segs.size(); ++i){
        cout << segs[i] << ' ';
    }
    cout << endl;

    vector<int> prefix;
    int sum = 0;
    for (int i = 0;i < segs.size(); ++i){
        prefix.push_back(sum+=segs[i]);
    }
    for (int i = 0;i < prefix.size(); ++i){
        cout << prefix[i] << ' ';
    }
    cout << endl;

    int qc;
    cin >> qc;
    int  ans;
    
    for (int k = 0; k < qc; ++k){
        int q, bad = 0, ll = 0, tail = 0;
        ans = 0;
        cin >> q;

        for (int i = 0; i < segs.size(); ++i) {
            if (segs[i] + ll-tail < q) {
                if (ll) bad += segs[i];
                ll += segs[i];
                cout << "add ll " << ll << " bad " << bad << endl;
            } else {
                tail = q - ll;
                if (ll) {
                    bad += tail;
                    ll = segs[i] - tail;
                } else {
                    tail = 0;
                    ll = 0;
                }
                cout << " end ll " << ll << " bad " << bad << endl;
                ans ++;
            }
        }
        if (ll) ans++;
        cout << ans << ' ' << bad << endl;
    }
}

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
                      

int s;



void next(int *ult, int n) {
    ult[0]++;
    for (int i = 0; i < n; ++i) {
        if (ult[i] > s) {
            ult[i+1] += ult[i] / (s+1);
            ult[i] = ult[i] % (s+1);
        }
    }
}

int main() {
    int n, p, q, tn;
    cin >> n >> s;
    tn = n * (s+1) * 2;

    //cout << tn << endl;

    int seq[tn], count[2*n];
    for (int i = 0; i < tn; ++i) cin >> seq[i];
    cin >> p;
    vector<int> ps, qs;

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

    sort(qs.begin(), qs.end());
    sort(ps.begin(), ps.end());

    int ult[2*n];
    for (int i = 0; i < 2*n; ++i) ult[i] = 0;

    long long max_v = (long long)pow(s+1, 2*n);

    long long team_a = 0, team_b = 0; 

    long long ans = 1000000007, mans = 0;

    //cout << max_v << endl;

    int posp, posq;

    for (int i = 0; i < max_v; ++i) {
        team_a = 0, team_b = 0;
        posp = ps.size()-1; posq = qs.size()-1;
        for (int j = 0; j < 2*n; ++j) count[j] = 0;

        for (int j = 0; j < tn; ++j) {
            int player = seq[j]-1;
                
            if (count[player] == ult[player]){
                // pick ult
                //cout << "Player " << player << " pick ult " << qs[posq] << endl;
                //cout << qs.size() << endl;
                if (player < n) {
                    team_a += qs[posq--];
                } else {
                    team_b += qs[posq--];
                }
            } else {
                // pick simple skill
                //cout << "Player " << player << " pick simple " << ps[posp] << endl;
                if (player < n) {
                    team_a += ps[posp--];
                } else {
                    team_b += ps[posp--];
                }
            }
            count[player]++;
        }    
        //cout << team_a << '|' << team_b << endl;
        if (abs(team_b - team_a) < abs(ans)) {
            ans = team_a - team_b;
            
        } 
        if (team_a - team_b == -ans){
            mans = team_a - team_b;
        }
        next(ult, 2*n);
    }

    //if (seq[0] <= n && abs(mans) == abs(ans)) {
    //    cout << abs(ans) << endl;
    //} else {
        cout << ans << endl;
    //}
    
}

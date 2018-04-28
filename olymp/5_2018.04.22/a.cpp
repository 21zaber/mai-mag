#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


int main(){
    int n;
    cin >> n;
    vector<int> a;
    set<pair<int, int> > l, g;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        a.push_back(t);
    }
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        t -= a[i];
        if (t > 0){
            g.insert(make_pair(t, i+1));
        } else if (t < 0){
            l.insert(make_pair(t, i+1));
        }
    }

    while (l.size() > 0){
        set<pair<int, int> >::iterator li = l.begin();
        set<pair<int, int> >::reverse_iterator gi = g.rbegin(), gin = g.rbegin();
        gin++;
        while (gin != g.rend() && abs(gi->first+li->first) > abs(gin->first+li->first)) ++gi, ++gin;
        //cout << gi->first << ' ' << gin->first << endl;

        int gof = gi->first;
        int gs = gi->second;
        int lof = li->first;
        int ls = li->second;
        int gn, ln, v;

        if (gof > -lof) {
            gn = gof + lof;
            ln = 0;
            v = -lof;
        } else {
            gn = 0;
            ln = lof + gof;
            v = gof;
        }
        cout << ls << " " << gs << " " << v << endl;
        l.erase(li);
        g.erase(g.find(make_pair(gof, gs)));
        if (ln < 0)
            l.insert(make_pair(ln, ls));
        if (gn > 0)
            g.insert(make_pair(gn, gs));

        //break;
    }
}

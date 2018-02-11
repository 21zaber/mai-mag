#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;


bool mycmp (pair<double, double> i,pair<double, double> j) { return (i.first>j.second); }

int main() {
    int m;
    cin >> m;
    for (int i=0;i<m;++i) {
        int n;
        double  l;
        cin >> n >> l;
        vector<pair<double, double> > lst(n+1);

        double b, c;
        for(int j=0;j<n;++j){
            cin >> b >> c;
            //cout << 2;
            c /= 1000000;
            b /= 1000;

            cout << 3;
            pair<double, double> x = make_pair(b, c);
            cout << 5;
            lst[j] = x;
        }
        cout << '*';

        sort(lst.begin(), lst.end(), mycmp);
      //for(int j = 0; j < lst.size(); ++j){
      //    cout << lst[j].first << ' ' << lst[j].second << endl;
      //
      //}

        double v =0, s=0, t=0;
        for (int j=0; j < n; ++j) {
//        for (int j=n-1; j >= 0; --j) {
            double a = lst[j].first;
            double tt = lst[j].second;
      //      cout << a << ' '<< tt;
            double ll = tt*(2*v + tt*a) /2;
            if (s + ll > l) {
        //        cout << 1;
                t += (-v + sqrt(v*v - 2*(s-l)*a)) / a;
                s = l;
                break;
            }
            s += ll;
            v += tt * a;
            t += tt;
         //   cout << s << ' '<< v << ' '<< t << ' ' << a <<  endl;
        }
        if (v > 0 and (l-s) > 0) 
            t += (l-s)/v;


        cout<<fixed<<setprecision(8)<<t<<endl;

        cout << '#';
        //lst.resize(0);

//        cout << t << endl;
    }


    return 0;
}




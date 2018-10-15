#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int n;
vector<int> a,b,c,d;

double dist(long long p1, long long q1, long long p2, long long q2){
    double ds = 0;
    double t1 = (double)p1/q1;
    double t2 = (double)p2/q2;

    for (int i = 0; i < n; ++i){
        double x = t1 * a[i] + (1 - t1) * b[i];
        double y = t2 * c[i] + (1 - t2) * d[i];

        ds += (x - y) * (x - y);
    }

    return ds;
}

int main() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    c.resize(n);
    d.resize(n);

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) cin >> c[i];
    for (int i = 0; i < n; ++i) cin >> d[i];

    long long inf = 81;

    long long lp1=-inf, lq1=1;
    long long rp1=inf, rq1=1;
    long long lp2, lq2;
    long long rp2, rq2;

    double ds = 100000000;

    while (1) {
        long long m1p = lp1 * rq1 + 2 * rp1 * lq1;
        long long m1q = lq1 * rq1;
        if (m1p % 3 == 0)
            m1p /= 3;
        else
            m1q *= 3;

        double d1 = 100000000;
        double d2 = 100000000;

        lp2=-inf, lq2=1;
        rp2=inf, rq2=1;

        while (1) {
            long long m3p = lp2 * rq2 + 2 * rp2 * lq2;
            long long m3q = lq2 * rq2;
            if (m3p % 3 == 0)
                m3p /= 3;
            else
                m3q *= 3;
            long long m4p = lp2 * rq2 * 2 + rp2 * lq2;
            long long m4q = lq2 * rq2;
            if (m4p % 3 == 0)
                m4p /= 3;
            else
                m4q *= 3;

            double d3 = dist(m1p, m1q, m3p, m3q);
            double d4 = dist(m1p, m1q, m4p, m4q);

            //cout << "d3 and d4: "<< d3 << ' ' << d4 << endl;

            if (d3 < d4){
                lp2 = m3p;
                lq2 = m3q;
                d1 = d3;
            } else {
                rp2 = m4p;
                rq2 = m4q;
                d1 = d4;
            }
            if (abs(d3 - d4) < 0.00001) break;
            //if (abs(lp2/lq2 - rp2/rq2) < 0.00001) break;
        }
        long long m2p = lp1 * rq1 * 2 + rp1 * lq1;
        long long m2q = lq1 * rq1;
        if (m2p % 3 == 0)
            m2p /= 3;
        else
            m2q *= 3;

        lp2=-inf, lq2=1;
        rp2=inf, rq2=1;

        while (1) {
            long long m3p = lp2 * rq2 + 2 * rp2 * lq2;
            long long m3q = lq2 * rq2;
            if (m3p % 3 == 0)
                m3p /= 3;
            else
                m3q *= 3;
            long long m4p = lp2 * rq2 * 2 + rp2 * lq2;
            long long m4q = lq2 * rq2;
            if (m4p % 3 == 0)
                m4p /= 3;
            else
                m4q *= 3;

            double d3 = dist(m2p, m2q, m3p, m3q);
            double d4 = dist(m2p, m2q, m4p, m4q);

            if (d3 < d4){
                lp2 = m3p;
                lq2 = m3q;
                d2 = d3;
            } else {
                rp2 = m4p;
                rq2 = m4q;
                d2 = d4;
            }
            if (abs(d3 - d4) < 0.00001) break;
            //if (abs(lp2/lq2 - rp2/rq2) < 0.00001) break;
        }

        //cout << "d1 and d2: "<< d1 << ' ' << d2 << endl;

        if (d1 < d2) {
            lp1 = m1p;
            lq1 = m1q;
            ds = d1;
        } else {
            rp1 = m2p;
            rq1 = m2q;
            ds = d2;
        }

      //cout << "" << lp1 << ' ' << lq1 << endl;
      //cout << "" << rp1 << ' ' << rq1 << endl;
      //
      //cout << "diff: " << abs((double)lp1/lq1 - (double)rp1/rq1) << endl;

        if (abs(d1 - d2) < 0.000001) break;
        //if (abs((double)lp1/lq1 - (double)rp1/rq1) < 0.00000001) break;
    }

    cout << ds << endl;

    long long tp1=lp1, tq1=lq1;
    long long tp2=lp2, tq2=lq2;

    long long p=0, q=tq1 * tq2;

    for (int i = 0; i < n; ++i) {
        long long t = 0;
        t += a[i] * tp1 * tq2;
        t -= b[i] * tp1 * tq2;
        t += b[i] * tq1 * tq2;
        t -= c[i] * tp2 * tq1;
        t += d[i] * tp2 * tq1;
        t -= d[i] * tq1 * tq2;
        p += t * t;
    }

    cout << p << " " << q*q << endl;
    cout << (double)p / (q * q) << endl;


}

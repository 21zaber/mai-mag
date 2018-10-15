#include <iostream>
#include <cmath>

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

int main() {
    int n, m, t;
    double s;
    cin >> t;
    cout.precision(15);
    for (int q = 0; q < t; ++q){
        cin >> n >> m >> s;

        elem k[n];
        for (int i = 0; i < n; ++i) k[i].c = 0;

        for (int i = 0; i < m; ++i){
            int x;
            cin >> x;
            k[x-1].c++;
        }

        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            k[i].m = x;
            k[i].p = y;
        }

        double l = 0, r = 1000000000;
        double m = 0;

        while (r - l > 0.000000000001) {
            m = l + (r-l) / 2.0;
            double sm = 0;

            for (int i = 0; i < n; ++i){
                if (k[i].m >= m * k[i].c) {
                    continue;
                }
                sm += (m * k[i].c - k[i].m) * k[i].p;
            }

            if (sm > s) {
                r = m;
            } else {
                l = m;
            }
        }
        cout << m << endl;
    }
}

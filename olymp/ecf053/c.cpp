#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int x, y;
    cin >> x >> y;

    if (n < abs(x)+abs(y) || n % 2 != abs(x+y) % 2) {
        cout << -1 << endl;
        return 0;
    }

    int px = 0, py = 0;

    int ldist[n+1], rdist[n+1], xl[n+1], yl[n+1], xr[n+1], yr[n+1];


    ldist[0] = abs(x) + abs(y);
    xl[0] = 0;
    yl[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'U') py += 1;
        if (s[i] == 'D') py -= 1;
        if (s[i] == 'L') px -= 1;
        if (s[i] == 'R') px += 1;
        xl[i+1] = px;
        yl[i+1] = py;

        ldist[i+1] = abs(x - px) + abs(y - py);
    }

    if (xl[n] == x && yl[n] == y) {
        cout << 0 << endl;
        return 0;
    }

    rdist[n] = 0;
    px = x, py = y;
    xr[n] = px;
    yr[n] = py;
    for (int i = n-1; i >= 0; --i) {
        if (s[i] == 'U') py -= 1;
        if (s[i] == 'D') py += 1;
        if (s[i] == 'L') px += 1;
        if (s[i] == 'R') px -= 1;
        xr[i] = px;
        yr[i] = py;

        rdist[i] = abs(x - px) + abs(y - py);
    }

    int l = 0, r = n;
    while (l < r) {
        int m = l + (r-l) / 2;
        bool f = false;

        for(int i = 0; i+m <= n; ++i) {
            int to = i+m;
//            cout << '\t' << xl[i] << ' ' << yl[i] << ' '  << xr[to] << ' '  << yr[to] << ' '  << endl;
            if (abs(xl[i] - xr[to]) + abs(yl[i] - yr[to]) <= m) {
                f = true;
                break;
            }
        }

//        cout << l << ' ' << r << ' ' << m << ' ' << f << endl;

        if (f) 
            r = m;
        else
            l = m+1;
    }

    cout << l << endl;
}

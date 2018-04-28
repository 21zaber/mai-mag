#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

#define ll long long 

map<ll, ll> smpl(ll a) {
    map<ll, ll> m;

    while (a % 2 == 0) {
        m[2]++;
        a /= 2;
    }
    ll l = sqrt(a) + 2;
    for (ll i = 3; i < a && i < l; i+=2) {
    //for (ll i = 3; i*i <= a; i+=2) {
        while (a % i == 0) {
            m[i]++;
            a /= i;
        }
    }
    if (a > 1) m[a]++;
    return m;
}

int main(){
    ll a, b = 1, c;
    cin >> a >> c;

    map<ll, ll> ad = smpl(a), cd = smpl(c);

    if (c % a != 0) {
        cout << -1 << endl;
        return 0;
    }

    for (auto i = cd.begin(); i != cd.end(); ++i) {
        ll k = i->first, n = i->second;
        auto p = ad.find(k);
        if (p == ad.end() || p->second < n) {
            b *= pow(k, n);
        }
    }

    cout << b << endl;

}

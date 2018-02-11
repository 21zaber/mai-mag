#include <iostream>
#include <vector>
using namespace std;


int main() {
	int n;
	cin >> n;
	
	// read mask
	vector<int> mask(n+1);
	for (int i = 1; i <= n; ++i) {
		cin >> mask[i];
	}
	
	// read edges
	vector<pair<int, int> > edges(n);
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		edges[i] = make_pair(a, b);
	}
	
	// find even and odd edges
	vector<int> is_odd(n+1, 0);
	for (int i = 0; i < n-1; ++i) {
		is_odd[edges[i].first] ^= 1;
		is_odd[edges[i].second] ^= 1;
	}
	
	// find xor for 0 changes
	int xr = n;
	for (int i = 1; i <= n; ++i) {
        // xr ^= i * is_odd[i];
		if (is_odd[i]) {
			xr ^= i;
		}
	}
	
	if (xr == 0) {
		// 0 changes needed
		cout << n << endl;
		for (int i = 0; i < n-1; ++i) {
			cout << edges[i].first << ' ' << edges[i].second << endl;	
		}
		return 0;
	}
	
	// find indices that can be changed
	vector<int> changeable;
	for (int i = 1; i <= n; ++i) {
		if (mask[i] && is_odd[i]) {
			changeable.push_back(i);
		}
	}

    int tmp_odd = 524288;
    for (int j = 0; j < n-1; ++j) {
        int i = edges[j].first;
        if (!is_odd[i] && mask[i]) {
            edges[j].first += tmp_odd;
        }
        i = edges[j].second;
        if (!is_odd[i] && mask[i]) {
            edges[j].second += tmp_odd;
        }
    }
	
	if (changeable.size() == 0) {
		cout << "-1" << endl;
		return 0;
	}
	
	if (changeable.size() == 1) {
		int ch = changeable[0];
		int xr2 = xr ^ ch;
		if (xr2 <= n && (is_odd[xr2] || !mask[xr2])) {
			cout << "-1" << endl;
			return 0;
		}
		
		cout << n << endl;
		for (int i = 0; i < n-1; ++i) {
			int a = edges[i].first;
			int b = edges[i].second;
			if (a == ch) {
				a = xr2;
			}
			if (b == ch) {
				b = xr2;
			}
			cout << a << ' ' << b << endl;
		}
		return 0;
	}
	
	int tmp = 262144;
	int ch1 = changeable[0];
	int ch2 = changeable[1];

    if ((ch1 ^ xr) == ch2) {
        if (changeable.size() == 2){
            cout << -1 << endl;
            return 0;
        }
        ch2 = changeable[2];
    }


	cout << n << endl;
	for (int i = 0; i < n-1; ++i) {
		int a = edges[i].first;
		int b = edges[i].second;
		if (a == ch1) {
			a = (ch1 ^ xr) + tmp;
		}
		if (a == ch2) {
			a = ch2 + tmp;
		}
		if (b == ch1) {
			b = (ch1 ^ xr) + tmp;
		}
		if (b == ch2) {
			b = ch2 + tmp;
		}
		cout << a << ' ' << b << endl;
	}
	
	return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>


using namespace std;

#define ll long long

ll C(ll n, ll k){
  if (k == 0 || n == k){
    return 1;
  }

  return C(n - 1, k - 1) + C(n - 1, k);
}


ll fun(const vector<pair<ll, int> > & a, int pos){
  vector<int> b(3, 0), c(3, 0);
  for (int i = 0; i < c.size(); ++i){
  	c[i] = i+1;
  }

  for (int i = pos+1; i < a.size() && 2 * a[pos].first >= a[i].first; ++i){
    b[a[i].second]++;
  }
   
  c[a[pos].second]--;
 
  ll res = 1;
  for (int i = 0; i < b.size(); ++i){
    if (b[i] < c[i])
    	return 0;
    res *= C(b[i], c[i]);
  }

  return res;
}


int main(){
	ios_base::sync_with_stdio(false);

  int g, d, f;
  cin >> g >> d >> f;
  
  vector<pair<ll, int> > a(g+d+f);
  
  for (int i = 0; i < g+d+f; ++i){
  	cin >> a[i].first;
  	
  	if(i < g){
  		a[i].second = 0;
  	}
  	else if (i < g + d){
  		a[i].second = 1;
  	}
  	else{
  		a[i].second = 2;
  	}
  }

  sort(a.begin(), a.end());

  ll res = 0;
  for (int i = 0; i< a.size(); ++i){
  	res += fun(a, i);
  }

  cout << res << endl;

  return 0;
}

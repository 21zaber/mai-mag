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

  vector<int> b(3, 0), c(3, 0);
  for (int i = 0; i < c.size(); ++i){
    c[i] = i+1;
  }
  for (int l = 0, r = l+1; l < a.size()-1; ++l){

    if (r <= l) {
        r = l+1;
        b.resize(3, 0);    
    }

    for (; r < a.size() && 2 * a[l].first >= a[r].first; ++r){
      b[a[r].second]++;
    }
     
    c[a[l].second]--;
   
    ll res_pos = 1;
    
    for (int i = 0; i < b.size(); ++i){
      if (b[i] < c[i]){
        res_pos = 0;
        break;
      }
      res_pos *= C(b[i], c[i]);
    }
    res += res_pos;
    
    c[a[l].second]++;
    
    if (l+1 < a.size()){
      b[a[l+1].second]--;
    }
  }
  cout << res << endl;

  return 0;
}

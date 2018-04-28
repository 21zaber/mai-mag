#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>


using namespace std;

#define ll long long

ll C1(ll n, ll k){
  if (k == 0 || n == k){
    return 1;
  }

  return C1(n - 1, k - 1) + C1(n - 1, k);
} 

long long C(int n, int k){
//    cout << n << ' ' << k << endl;
    if (k == 0 || k == n) return 1;
    //if (n < k) return 0;
    if (k == 1) return n;
    if (k == 2) return (n * (n-1)) / 2;
    if (k == 3) return (n * (n-1) * (n-2)) / 6;
    return 0;
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
  
  for (int i = 0; i < a.size(); ++i){
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
  vector<int> b(3, 0), c(3, 0);
  for (int i = 0; i < 3; ++i) c[i] = i+1;


  //cout << "1\n" << flush;
  int r = 1;

  ll res = 0;
  for (int i = 0; i < a.size()-1; ++i){

      //cout << "1" << flush;
      for (; r < a.size() && 2 * a[i].first >= a[r].first; ++r){
        b[a[r].second]++;
      }
      //cout << "2" << flush;
       
      c[a[i].second]--;

      //cout << "b: " << b[0] << " " << b[1] << " " << b[2] << endl;
    //cout << "b.size: " << b.size() << endl;

     
      ll tmp_res = 1;
      for (int j = 0; j < 3; ++j){
        if (b[j] < c[j]){
            tmp_res = 0;
            break;
        }
    //    cout << i << " " << b[i] << " " << c[i] << endl;
        tmp_res *= C(b[j], c[j]);
      }
      //cout << "3" << flush;
      c[a[i].second]++;
      res += tmp_res;
      b[a[i+1].second]--;
  }

  cout << res << endl;

  return 0;
}

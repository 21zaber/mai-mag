#include <set>
#include <iostream>

using namespace std;

long long fun(vector<pair<int, int> > a, int pos){
    vector<int> b(3, 0), c(3, 0);
    for (int i = pos+1; i < a.size() && 2 * a[pos].first >= a[i].first; ++i){
        b[a[i].second]++;
    }

    c[a[pos].second]--;
   
    long long res = 1;
    for (int i = 0; i < b.size(); ++i){
        if (b[i] < c[i]) return 0;
        res *= c(b[i], c[i]);
    }
    return res;
}

int main(){
    set<int> a;
    a.insert(10);
    a.insert(19);

    cout << *(a.lower_bound(20)) << endl;
    cout << (a.lower_bound(20) == a.end()) << endl;

    cout << sizeof(int) << endl;
    cout << sizeof(long) << endl;

}

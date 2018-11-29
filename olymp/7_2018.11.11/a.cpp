#include <bits/stdc++.h>

using namespace std;

#define T 0.000000000000000001

#define double long double

pair<double, double> n(double a, double b, double c) {
    if (!a) return make_pair(0, 1);
    if (!b) return make_pair(1, 0);

    double x = sqrt(a*a + b*b);

    return make_pair((double)a/x, (double)b/x);
}

//  double l(double a, double b, double c, double x, double y){
//      return -(a*x +b*y + c)/sqrt(a*a + b*b);
//  }
pair<double, double> v1,v2,v3,v4;
double x, y;

double check2(double m1, double m2){
    double x1 = (v3.first - v1.first) * m1 + v1.first; 
    double y1 = (v3.second - v1.second) * m1 + v1.second; 
    double x2 = (v4.first - v2.first) * m2 + v2.first; 
    double y2 = (v4.second - v2.second) * m2 + v2.second;

    //cout << x1 << ' ' << y1 << "; " << x2 << ' ' << y2 << endl;

    return sqrt(x1*x1 + y1*y1) + sqrt(x2*x2 + y2*y2) + sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double check1(double m1){
    double l=0, r=1;

    while (abs(r-l) > T) {
        double c1 = (r - l) * 1 / 3 + l;
        double c2 = (r - l) * 2 / 3 + l;

        if (check2(m1, c1) < check2(m1, c2))
            r = c2;
        else
            l = c1;
    }

    return l;
}

double dist(double x1, double y1, double x2, double y2) {
    double a = x1 - x2;
    double b = y1 - y2;

    return sqrt(a*a + b*b);
}

int main() {
    double a1, b1, c1;
    double a2, b2, c2;


    cin >> a1 >> b1 >> c1;
    c1 *= -1;
    cin >> a2 >> b2 >> c2;
    c2 *= -1;


    if (a1 && b1){
        v1.first = 1000000000;
        v1.second = (-c1 - a1 *v1.first) / b1;
        v3.first = -1000000000;
        v3.second = (-c1 - a1 *v3.second) / b1;
    } else {
        if (a1) {
            v1.second = 0;
            v3.second = 0;

            v1.first = 1000000000;
            v3.first = -1000000000;
        } else {
            v1.first = 0;
            v3.first = 0;

            v1.second = 1000000000;
            v3.second = -1000000000;
        }
    }
    if (a2 && b2){
        v2.first = 1000000000;
        v2.second = (-c2 - a2 *v2.first) / b2;
        v4.first = -1000000000;
        v4.second = (-c2 - a2 *v4.second) / b2;
    } else {
        if (a2) {
            v2.second = 0;
            v4.second = 0;

            v2.first = 1000000000;
            v4.first = -1000000000;
        } else {
            v2.first = 0;
            v4.first = 0;

            v2.second = 1000000000;
            v4.second = -1000000000;
        }
    }

    cout << fixed << setprecision(10)<< v1.first << ' ' << v1.second << endl;
    cout<< fixed << setprecision(10)<< v2.first <<  ' ' << v2.second << endl;
    cout<< fixed << setprecision(10)<< v3.first << ' ' << v3.second << endl;
    cout<< fixed << setprecision(10)<< v4.first <<  ' ' << v4.second << endl;

    double l = 0, r = 1;
    double ans = 0;

    while (abs(r - l) > T) {
        double k1 = (r - l) * 1 / 3 + l;
        double k2 = (r - l) * 2 / 3 + l;

        double ans1 = check1(k1);
        double ans2 = check1(k2);

        ans = check2(k1, ans1);

        if (ans < check2(k2, ans2))
            r = k2;
        else
            l = k1;
    }

    cout << fixed << setprecision(10) << ans << endl;

    return 0;

//  v1 = n(a1, b1, c1);
//  v2 = n(a2, b2, c2);
//  double l1 = l(a1, b1, c1, 0, 0);
//  double l2 = l(a2, b2, c2, 0, 0);
//
//  v1.first *= l1;
//  v1.second *= l1;
//  v2.first *= l2;
//  v2.second *= l2;
//
//  v3 = n(a1, b1, c1);
//  v4 = n(a2, b2, c2);
//  double l3  = l(a1, b1, c1, v2.first, v2.second);
//  double l4  = l(a2, b2, c2, v1.first, v1.second);
//  v3.first *= l3;
//  v3.second *= l3;
//  v4.first *= l4;
//  v4.second *= l4;
//
//  v3.first += v2.first;
//  v3.second += v2.second;
//  v4.first += v1.first;
//  v4.second += v1.second;
//
//
//  double ll = l1 + l2;
//  double q = v1.first - v2.first;
//  q *= q;
//  double w = v1.second - v2.second;
//  w *= w;
//
//  ll += sqrt(q + w);
//
////cout << v1.first << ' ' << v1.second << endl;
////cout << v2.first <<  ' ' << v2.second << endl;
////
////cout << '\t' << l1 << ' ' << l2 << endl;
//
//  if (b1*a2 == b2* a1) {
//      cout << fixed << setprecision(10) << ll << endl;
//      return 0;
//  }
//
////if (a1*b1 + a2*b2 > 0){
////    cout << fixed << setprecision(10) << 2* max(l1, l2) << endl;
////    return 0;
////}
//
//  
////ll = 0;
////double qwe = v1.first*2 - v2.first * 2;
////ll += qwe*qwe;
////qwe = v1.second*2 - v2.second * 2;
////ll += qwe*qwe;
////ll = sqrt(ll);
////
////if (ll > 2*l1 && ll > 2 * l2){
////    cout << fixed << setprecision(10) << sqrt(ll)  << endl;
////    return 0;
////} else {
////    cout << fixed << setprecision(10) << 2* max(l1, l2)  << endl;
////    return 0;
////}
//
//
//
//  y = -(c1*a2 - a1*c2) / (b1*a2 - a1*b2) ;
//  x = 0;
//
//  if (a1 && b1)
//      x = (-c1 - b1*y) / a1;
//  else if (a2 && b2) 
//      x = (-c2 - b2*y) / a2;
//  else
//      if (a1)
//          x = -c1 / a1;
//      else
//          x = -c2 / a2;
//  
////cout << l3 << ' ' << l4 << endl;
////
////cout << v1.first << ' ' << v1.second << endl;
////cout << v2.first <<  ' ' << v2.second << endl;
////cout << v3.first << ' ' << v3.second << endl;
////cout << v4.first <<  ' ' << v4.second << endl;
//
//  if (dist(v1.first, v1.second, x, y) > dist(v1.first, v1.second, v3.first, v3.second)){
//    v3.first = x;
//    v3.second = y;
//  }
//  if (dist(v2.first, v2.second, x, y) > dist(v2.first, v2.second, v4.first, v4.second)){
//      v4.first = x;
//      v4.second = y;
//  }
//
//  double l = 0, r = 1;
//  double ans = 0;
//
//  while (abs(r - l) > T) {
//      double k1 = (r - l) * 1 / 3 + l;
//      double k2 = (r - l) * 2 / 3 + l;
//
//      double ans1 = check1(k1);
//      double ans2 = check1(k2);
//
//      ans = check2(k1, ans1);
//
//      if (ans < check2(k2, ans2))
//          r = k2;
//      else
//          l = k1;
//  }
//
//  cout << fixed << setprecision(10) << ans << endl;
}

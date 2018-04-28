#include <iostream>
#include <vector>

using namespace std;

int main() {
    int a,b,c;
    cin >> a >> b >> c;
    //     5    4    3
    if (c == 0 && b == 0){
        cout << a+1 << endl;
        for (int  i = 0 ; i < a; ++i) cout << a+1 << ' ';
        cout << 0 << endl;
        for (int  i = 0 ; i < a; ++i) cout << "5 ";
        cout << 0 << endl;
        return 0;
    }
    if (c == 0 && a == 0) {
        cout << b+1 << endl;
        for (int  i = 0 ; i < b; ++i) cout << b+1 << ' ';
        cout << 0 << endl;
        for (int  i = 0 ; i < b; ++i) cout << "4 ";
        cout << 0 << endl;
        return 0;
    }
    if (c == 0) {
        cout << b + a * 2 + 1 << endl;
        for (int  i = 0 ; i < b; ++i) cout << b+1 << ' ';
        cout << b+3 << ' ';
        for (int i = 0; i < a-1; ++i) cout << b+3+i*2 << ' ' << b+5+i*2 << ' ';
        cout << b+1+a*2 << " 0" << endl;

        for (int  i = 0 ; i < b; ++i) cout << "4 ";
        cout << "0 ";
        for (int i = 0; i < a; ++i) cout << "5 0 ";
        cout <<  endl;
        return 0;
    }
    cout << c + 2 * (b + a) + 1 << endl;
    int p = c;
    for (int  i = 0 ; i < c; ++i) cout << p + 1 << ' ';
    p += 3;
    for (int  i = 0 ; i < b; ++i) cout << p + i*2 << ' ' << p +i*2 << ' ';
    p += b * 2;
    for (int  i = 0 ; i < a; ++i) cout << p + i*2 << ' ' << p + i*2 << ' ';
    cout << 0 << endl;

    for (int i = 0; i < c; ++i) cout << "3 ";
    for (int i = 0; i < b; ++i) cout << "0 4 ";
    for (int i = 0; i < a; ++i) cout << "0 5 ";
    cout << 0 << endl;
}

#include <iostream>
#include <string>
#include <cmath>

using namespace std;



int main() {
    int t;
    cin >> t;
    for (int a =0; a < t; ++a) {
        int h, w;
        cin >> h >> w;
        string s;
        cin >> s;
        int m[h][w], ans[h][w];
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> m[i][j];
                ans[i][j] = 0;
            }
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int c = m[i][j];
                int x = i, y = j;
                for (int k = 0; k < s.size(); ++k) {
                    char d = s[k];
                    if (d == 'D') {
                        x += 1;
                    } else if (d == 'U') {
                        x -= 1;
                    } else if (d == 'L') {
                        y -= 1;
                    } else if (d == 'R') {
                        y += 1;
                    }

                    if (x < 0 || x >= h || y < 0 || y >= w){
                        c = 0;
                        break;
                    }
                    c += m[x][y];
                }
                ans[i][j] = c;
            }
        }
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cout << ans[i][j] << ' ';
            }
            cout << endl;
        }
    }


}

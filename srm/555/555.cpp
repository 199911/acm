#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

struct XorBoard {
  LL H, W, RC, CC, MOD; 
  LL C[2400][2400];

  void init() {
    MOD = 555555555;
    CLR( C, 0 );
    for( int i = 0; i < 2400; i++ ) C[i][0] = 1;
    FOR( i, 1, 2400 ) 
      FOE( j, 1, i ) {
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
      }
  }

  LL cnt( LL r, LL c ) {
    LL ans = 1;
    ans *= C[H][r];
    ans %= MOD;
    ans *= C[W][c];
    ans %= MOD;
    
    if ( (RC - r) & 1 ) return 0;
    if ( (CC - c) & 1 ) return 0;

    LL t = ( RC - r ) / 2, u = ( CC - c ) / 2;
    ans *= C[H + t - 1][t]; 
    ans %= MOD;
    ans *= C[W + u - 1][u];
    ans %= MOD;

    return ans;
  }

  int count( int h, int w, int r, int c, int s ) {
    H = h; W = w; RC = r; CC = c;
    LL ans = 0;
    init();
    for( LL rw = 0; rw <= min(r, h); rw++ ) {
      for( LL cl = 0; cl <= min(c, w); cl++ ) {
        LL ct = rw * w + cl * h - 2 * rw * cl;
        if ( ct == s ) {
          ans += cnt( rw, cl );
          ans %= MOD;
        }
      }
    }

    return ans;
  }
};

int main() {
  int h, w, r, c, s;
  cin >> h >> w >> r >> c >> s;
  cout << HI.count( h, w, r, c, s ) << endl;
  return 0;
}

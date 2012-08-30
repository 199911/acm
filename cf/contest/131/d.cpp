#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
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

#define MOD 1000000007

int c[111][111];

int main() {
  CLR( c, 0 );

  for ( int i = 0; i <= 100; i++ ) {
    c[i][0] = 1;
    c[i][1] = i;
  }

  for ( int i = 1; i <= 100; i++ ) {
    for ( int j = 2; j <= i; j++ ) {
      c[i][j] = c[i-1][j-1] + c[i-1][j] % MOD;
    }
  }

  int a[10], n, s = 0;
  cin >> n;
  REP( i, 10 ) {
    cin >> a[i];
    s += a[i];
  }

  if ( s > n ) {
    puts( "0" );
    return 0;
  } else {
    LL res = 1, fl = s, res2 = 1;
    REP( i, 10 ) {
      res *= c[fl][a[i]];
      res %= MOD;
      fl -= a[i];
    }

    if ( a[0] ) {
      fl = s - 1;
      a[0]--;

      REP( i, 10 ) {
        res2 *= c[fl][a[i]];
        fl -= a[i];
      }

      res2 = res - res2; 
    } else {
      res2 = res;
    }
    LL ans = 0;
    REP( i, n - s + 1 ) {
      LL tmp = i ? res : res2;

      printf( "[%d]: %lld\n", i, tmp );
      REP( j, i ) {
        tmp *= 9;
        tmp %= MOD;
      }
      tmp *= c[n-i][s];
      tmp %= MOD;

      REP( j, n - s - i ) {
        tmp *= 10;
        tmp %= MOD;
      }

      printf( "tmp = %lld\n", tmp );

      ans += tmp;
      ans %= MOD;
    }

    cout << ans << endl;
  }
  return 0;
}

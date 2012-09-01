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

#define MOD 1000000007LL

int a[11], n;
LL dp[11][111], c[111][111];

int main() {
  CLR( c, 0 );
  REP( i, 111 ) c[i][0] = 1;
  FOR( i, 1, 111 ) FOE( j, 1, i ) c[i][j] = ( c[i - 1][j - 1] + c[i - 1][j] ) % MOD;

  cin >> n;
  REP( i, 10 ) cin >> a[i];

  CLR( dp, 0 );

  int len = 0;
  for( int i = a[1]; i <= n; i++ ) dp[1][i] = 1; 
  len = a[1];
  FOR( i, 2, 10 ) {
    for( int l = len + a[i]; l <= n; l++ ) {
      for( int j = a[i]; j <= l - len; j++ ) {
        dp[i][l] += dp[i - 1][l - j] * c[l][j] % MOD;
        dp[i][l] %= MOD;
      }
    }
    len += a[i];
  }

  LL ans = 0;
  for( int l = a[0] + len; l <= n; l++ ) {
    if ( l == 0 ) continue;
    for( int i = a[0]; i <= l - len; i++ ) {
      int k = l - i;
      ans += dp[9][k] * c[l - 1][i] % MOD;
//      cout << "(" << k << ") * (" << i << ") : " << dp[9][k] << "*" << c[l - 1][i] << endl;
      ans %= MOD;
    }
  }

  cout << ans << endl;

  return 0;
}

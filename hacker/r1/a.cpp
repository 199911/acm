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

#define MOD 1000000007LL

LL c[10011][10011];
LL a[11111], s[11111], ans;
int n, k, T;

int main() {
  scanf( "%d", &T );
  CLR( c, 0 );
  FOE( i, 0, 10002 ) c[i][0] = 1;
  FOE( i, 1, 10002 ) {
    FOE( j, 1, i ) {
      c[i][j] = ( c[i - 1][j - 1] + c[i - 1][j] ) % MOD;
    }
  }
  for( int cas = 1; cas <= T; cas++ ) {
    scanf( "%d%d", &n, &k );
    REP( i, n ) scanf( "%lld", &a[i] );
    REP( i, n ) s[i] = a[i];
    sort( s, s + n );
    ans = 0;
    REP( i, n ) {
      ans += s[i] * c[i][k - 1];
      ans %= MOD;
    }
    printf( "Case #%d: %lld\n", cas, ans );
  }
  return 0;
}

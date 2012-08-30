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

#define N 11111

int p[N], g[N], ans, a[N], n, sm = 1<<29;

int main() {
  scanf( "%d", &n );
  REP( i, n ) scanf( "%d", &g[i] );
  REP( i, n ) a[i] = g[i], sm = min( sm, g[i] );
  sort( a, a + n );
  REP( i, n ) p[i] = lower_bound( a, a + n, g[i] ) - a;
  CLR( a, 0 );

  ans = 0;
  REP( i, n ) {
    if ( !a[i] ) {
      int ptr = i, mi = 1<<29, cnt = 0, sum = 0;
      do {
        mi = min( mi, g[ptr] );
        sum += g[ptr];
        cnt++;
        ptr = p[ptr];
        a[ptr] = 1;
      } while( ptr != i );
      if ( cnt > 1 ) {
        int cur1 = sum + mi * ( cnt - 2 ), cur2 = sm * (cnt + 1) + mi + sum;
        ans += min( cur1, cur2 );
      }
    }
  }

  printf( "%d\n", ans );
  return 0;
}

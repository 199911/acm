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

LL gcd( LL a, LL b ) { return b ? gcd( b, a % b ) : a; } 

// enumerate f_MAX
int MAX;

void dfs( int lm, int ln, int rm, int rn ) {
  int cm = lm + rm, cn = ln + rn;
  if ( cn > MAX ) return;
  dfs( lm, ln, cm, cn );
  printf( "%d / %d\n", cm, cn );
  dfs( cm, cn, rm, rn );
}

#define SQRTN 1111

LL C[SQRTN], D[SQRTN];

void precompute( int n ) {
  for ( int r = 1; r * r <= n; r++ ) D[r] = 1;
  for ( int r = 1; r * r <= n; r++ ) 
    for ( int t = 2; t <= r; t++ ) 
      D[r] -= D[r / t];

  int m;
  for ( m = 1; m * m <= n; m++ ) C[m] = 1;
  for ( int q = m - 1; q >= 1; q-- )
    for ( int t = q + q; t <= n; t += q ) 
      C[q] -= t * t <= n ? C[t] : D[n / t];
}

LL rank( LL no, LL de, LL n ) {
  LL cnt = 0;
  for ( int i = 1; i <= n; i++ )  
    cnt += ( i * i <= n ? C[i] : D[n / i] ) * i * no / de;
  return cnt;
}

void farey( LL n, LL k, LL &no, LL &de ) {
  LL lo = 0, hi = n + 1, mi;

  precompute( n );
  while ( lo + 1 < hi ) {
    mi = ( lo + hi ) >> 1;
    printf( "rank[%lld] = %lld\n", mi, rank(mi, n, n) );
    if ( rank( mi, n, n ) <= k ) lo = mi;
    else hi = mi;
  }

  LL mp[3], mq[3];

  mp[0] = hi; mp[1] = hi;
  mq[0] = n; mq[1] = n;

  for ( LL q = 1; q <= n; q++ ) {
    LL p = (lo * q + n - 1 ) / n;
    if ( gcd( p, q ) > 1 ) continue;
    if ( p * mq[0] < q * mp[0] ) {
      mp[1] = mp[0]; mq[1] = mq[0];
      mp[0] = p; mq[0] = q;
    } else if ( p * mq[1] < q * mp[1] ) {
      mp[1] = p; mq[1] = q;
    }
  }

  printf( "lo = %lld(%lld)\n", lo, rank(lo, n, n) );

  LL kk = k - rank( lo, n, n );

  if ( kk < 2 ) {
    no = mp[kk]; de = mq[kk];
    return;
  }

  printf("1: %lld/%lld\n2: %lld/%lld\n", mp[0], mq[0], mp[1], mq[1]);
  for ( int i = 2; i <= kk; i++ ) {
    mp[i % 3] = (mq[(i - 2) % 3] + n) / mq[(i - 1) % 3] * mp[(i - 1) % 3] - mp[(i - 2) % 3];
    mq[i % 3] = (mq[(i - 2) % 3] + n) / mq[(i - 1) % 3] * mq[(i - 1) % 3] - mq[(i - 2) % 3];
    printf( "%d: %lld/%lld\n", i, mp[i % 3], mq[i % 3] );
  }

  no = mp[kk % 3]; de = mq[kk % 3];
}

int main() {
  LL n, k;
  while ( cin >> n >> k ) {
    LL p, q;
    farey( n, k, p, q );
    printf( "%lld/%lld\n", p, q );
  }
  return 0;
}

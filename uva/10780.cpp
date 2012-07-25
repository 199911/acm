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

#define N 11111
#define M 5555

bool ip[N];
LL p[N], pn, ff[N];

void seive( int n ) {
  pn = 0;
  CLR( ip, 1 );
  REP( i, n ) ff[i] = i;
  FOR( i, 2, n ) {
    if ( ip[i] ) {
      p[pn++] = i;
      for ( int j = i + i; j < n; j += i ) {
        if ( ff[j] == j ) ff[j] = i;
        ip[j] = 0;
      }
    }
  }
}

void reduce( LL s[], LL k ) {
  for ( int i = k; i >= 2; i-- ) {
    if ( !ip[i] ) {
      s[ff[i]] += s[i];
      s[i/ff[i]] += s[i];
      s[i] = 0;
    }
  }
}

void factorize( LL x, LL pf[], LL pe[], LL &r ) {
  LL res = x;
  r = 0;
  for ( int i = 0; res > 1 && i < pn && SQR(p[i]) <= x; i++ ) {
    if ( res % p[i] == 0 ) {
      pf[r] = p[i];
      pe[r] = 0;
      while ( res % p[i] == 0 ) {
        pe[r]++;
        res /= p[i];
      }
      r++;
    }
  }
  if ( res > 1 ) {
    pf[r] = res;
    pe[r++] = 1;
  }
}

int main() {
  int T;
  seive( N );
  scanf( "%d", &T );
  REP( cas, T ) {
    LL n, m;
    scanf( "%lld%lld", &m, &n );

    LL ps[N], pf[N], pe[N], r, ans = 1 << 29;

    CLR( ps, 0 );
    FOE( i, 2, n ) ps[i] = 1;
    reduce( ps, n );

    factorize( m, pf, pe, r );

    REP( i, r ) {
      ans = min( ans, ps[pf[i]] / pe[i]);
    }

    printf("Case %d:\n", cas + 1);
    if ( ans ) printf( "%d\n", ans );
    else puts( "Impossible to divide" );
  }
  return 0;
}

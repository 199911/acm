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
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
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
#define gm(a,b) (((a)%(b)+(b))%(b))

LL gcd( LL a, LL b ) {
  return b ? gcd( b, a % b ) : a;
}

int egcd( int a, int b, int &s, int &t ) {
  if ( b == 0 ) { 
    s = 1; t = 0; 
    return a;
  } 
  LL r = egcd(b, a % b, t, s );
  t -= ( a / b ) * s;
  return r;
}

int inv( int a, int m ) {
  int s, t;
  if ( egcd( a, m, s, t ) > 1 ) return -1;
  return gm(s,m);
}

pair<LL,int> amp[100000];

LL dlg( LL a, LL b, LL n ) {
  LL am = 1, m;
  pair<LL, int> *j;
  for( m = 0; m * m < n; m++ ) {
    amp[m] = make_pair(am, (int)m);
    am = ( am * a ) % n;
  }
  sort( amp, amp + m );
  am = inv( am, n );
  b %= n;
  for( int i = 0; i <= m; i++ ) {
    j = lower_bound( amp, amp + m, make_pair( b, -1 ) );
    if ( j != amp + m && j->first == b ) 
      return i * m + j->second;
    b = ( b * am ) % n;
  }
  return -1;
}

LL gdlg( LL a, LL b, LL n ) {
  LL tn = n, am = 1, g, i;
  while( ( g = gcd( a, tn ) ) > 1 ) tn /= g;
  for( i = 0; ( 1LL << i ) <= n; i++ ) {
    if ( am == b ) return i;
    am = ( am * a ) % n;
  }
  if ( b % ( n / tn ) ) return -1;
  LL r = dlg( a, b * inv( am, tn ), tn );
  if ( r < 0 ) return -1;
  return r + i;
}

LL a, b, n, ans;

int main() {
  while( scanf( "%lld%lld%lld", &n, &a, &b ) != EOF ) {
    LL ans = gdlg( a, b, n );
    if ( ans < 0 ) puts( "no solution" );
    else printf( "%lld\n", ans );
  }
  return 0;
}

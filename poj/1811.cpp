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

inline LL min( LL a, LL b ) { return a < b ? a : b; }

inline LL gcd( LL a, LL b ) { return b ? gcd( b, a % b ) : a ; }

inline LL mul( LL a, LL b, LL m ) {
  a %= m; b %= m;
  LL t = 0;
  while ( b ) {
    t += a * ( b & 255 );
    t %= m;
    a <<= 8;
    b >>= 8;
    a %= m;
  }
  return t;
}

inline LL exp( LL a, LL b, LL m ) {
  LL res = 1;
  while ( b ) {
    if ( b & 1 ) res = mul( res, a, m );
    a = mul( a, a, m );
    b >>= 1;
  }
  return res;
}

inline LL func( LL a, LL b, LL n ) {
  LL t = mul( a, a, n ) + b;
  if ( t >= n ) return t - n;
  return t;
}

inline LL func( LL a, LL n ) {
  LL t = mul(a, a, n) + 1;
  if ( t == n ) return 0;
  return t;
}

inline bool witness( LL p, LL a ) {
  int s = 0;
  LL t = p - 1;
  while ( !(t & 1) ) {
    s++; t >>= 1;
  }

  a = exp( a, t, p );

  if ( a == 1 || a + 1 == p ) return 0;
  while ( --s ) {
    a = mul ( a, a, p );
    if ( a + 1 == p ) return 0;
  }
  return 1;
}

bool isprime( LL p ) {
  if ( p == 2 ) return 1;
  if ( !(p & 1) || p < 2 ) return 0;

  LL s = 1;
  
  for ( int r = 0; r < 16; r++ ) {
    s = func( s, p );
    if ( !s ) s = r % ( p - 1 ) + 1;
    if ( witness( p, s ) ) 
      return 0;
  }

  return 1;
}

LL rho ( LL p, LL t ) {
  LL x = 2, y = 2, d;
  do {
    x = func( x, t, p );
    y = func( func(y, t, p), t, p );
    d = gcd( x - y, p );
    if ( d < 0 ) d = -d;
  } while ( d == 1 );
  return d;
}

// return the smallest factor 
LL rfactor( LL x ) {
  if ( isprime(x) ) return x; 
  if ( (x & 1) == 0 ) return 2;


  LL t = rho( x, 1 );
  for ( LL c = 2; t == x; c++ ) t = rho( x, c );

  if ( t * t == x ) return rfactor( t ); 
  return min( rfactor( t ), rfactor( x / t ) );
}

int main() {
  LL n, x;
  scanf( "%lld", &n );
  while ( n-- ) {
    scanf ( "%lld\n", &x );
    LL f;
    if ( x & 1 == 0 ) 
      f = 2;
    else 
      f = rfactor( x );
    if ( f == x ) printf( "Prime\n" );
    else printf( "%lld\n", f );
  }

  return 0;
}

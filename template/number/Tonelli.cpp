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

LL exp( LL a, LL b, LL c ) {
  LL ret = 1;
  while ( b ) {
    if ( b & 1 ) ret = ret * a % c;
    a = a * a % c;
    b >>= 1;
  }
  return ret;
}

// assume p is a prime
LL legendre( LL a, LL p ) {
  return exp( a, ( p - 1 ) / 2, p );
}

LL Tonelli( LL a, LL p ) {
  a %= p;
  if ( legendre( a, p ) != 1 ) return -1;
  LL Q = p - 1, S = 0;
  while( Q % 2 == 0 ) Q /= 2, S++;
  if ( S == 1 ) {
    LL ret = exp( a, ( p + 1 ) / 4, p );
    return min( p - ret, ret );
  }
  LL z = 1;
  while( legendre( z, p ) != p - 1 ) z++;
  LL c = exp( z, Q, p ), R = exp( a, (Q + 1) / 2, p ), t = exp( a, Q, p ), M = S;
  while( t !=1 ) {
    LL i = 1;
    while( exp( t, 1LL << i, p ) != 1 ) i++;
    LL b = exp( c, 1LL << ( M - i - 1 ), p );
    R = R * b % p;
    c = b * b % p;
    t = t * c % p;
    M = i;
  }
  return min( R, p - R );
}

int main() {
  LL n, a, p;
  scanf( "%lld", &n );
  while( n-- ) {
    scanf( "%lld%lld", &a, &p );
    if ( p == 2 ) {
      if ( a == 0 ) printf( "0\n" );
      else printf( "1\n" );
    } else {
      LL ans = Tonelli( a, p );
      if ( ans < 0 ) {
        printf( "No root\n" );
      } else {
        printf( "%lld %lld\n", ans, p - ans );
      }
    }
  }
  return 0;
}

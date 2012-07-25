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

#define N (1<<17)

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

bool ip[N];
LL p[N], pn;

void seive( LL n ) {
  CLR(ip, 1);
  ip[0] = ip[1] = 0;
  pn = 0;
  for( LL i = 2; i < n; i++ ) {
    if ( ip[i] ) {
      p[pn++] = i;
      for ( int j = i + i; j < n; j += i ) 
        ip[j] = 0;
    }
  }
}

void factorize( LL x, LL pf[], LL pe[], LL &r ) {
  LL res = x;
  r = 0;
  for ( int i = 0; res > 1 && i < pn && SQR(p[i]) <= x; i++ ) {
    if ( res % p[i] == 0 ) {
      pf[r] = p[i];
      pe[r]  =0;
      while ( res % p[i] == 0 ) {
        res /= p[i];
        pe[r]++;
      }
      r++;
    }
  }

  if ( res > 1 ) {
    pf[r] = res;
    pe[r++] = 1;
  }
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

int main() {
  LL x;
  seive(N);
  while ( scanf( "%lld", &x ) != EOF ) {
    LL pf[1111], pe[1111], r;

    factorize(x, pf, pe, r);

    LL cnt = 1;


    for ( int i = 0; i < r; i++ ) {
      if ( pf[i] == 2 ) continue;
      if ( pf[i] >= N ) {
        LL res = pf[i];
        if ( isprime( res ) ) {
          cnt *= 2;
        } else {
          LL s = (LL) sqrt( res + 1e-6);
          if ( SQR(s) == res ) {
            cnt *= 3;
          } else {
            cnt *= 4;
          }
        }
      } else {
        cnt *= pe[i] + 1;
      }
    }

    printf( "%lld\n", cnt );

  }
  return 0;
}

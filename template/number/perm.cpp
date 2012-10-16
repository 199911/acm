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
#define NOR(a,n) (((a)%(n)+(n))%(n))

// given two permutation A, B, find n such that A ^ n = B
#define N 555
#define PLL pair<LL,LL>

LL gcd( LL a, LL b ) { return b ? gcd( b, a % b ) : a; }

LL egcd( LL a, LL b, LL &s, LL &t ) {
  if ( b == 0 ) { 
    s = 1; t = 0; 
    return a;
  } 
  LL r = egcd(b, a % b, t, s );
  t -= ( a / b ) * s;
  return r;
}

LL inv( LL a, LL n ) {
  LL s, t, r;
  r = egcd( a, n, s, t );
  if ( r != 1 ) return -1;
  return NOR(s,n);
}

bool solve( LL a, LL b, LL m, PLL &ans ) {
  LL r = gcd( a, m );
  if ( b % r ) return false;
  a /= r; b /= r; m /= r;
  LL ia = inv( a, m ), c = NOR( ia * b, m );
  ans = PLL( c, m );
  return true;
}

bool merge( PLL a, PLL b, PLL &ans ) {
  PLL tmp; 
  if ( solve( a.second, b.first - a.first, b.second, tmp ) ) {
    LL m = tmp.second * a.second, c = NOR(a.first + a.second * tmp.first, m);
    ans = PLL( c, m );
    return true;
  }
  return false;
}

LL lg( int A[], int B[], int n ) {
  int idx[N], cyc[N], sz[N], off[N], cn = 0;
  CLR( idx, -1 );
  REP( i, n ) {
    if ( idx[i] == -1 ) {
      int ptr = i, dx = 0;
      do {
        cyc[ptr] = cn;
        idx[ptr] = dx++;
        ptr = A[ptr];
      } while( ptr != i );
      sz[cn++] = dx;
    }
  }

  // check whether the cycle match
  int cur = 0, ok = 1;
  REP( i, n ) {
    if ( cyc[i] == cur ) {
      int ptr = i, k = -1;
      do {
        ptr = A[ptr];
        if ( cyc[ptr] == cyc[B[ptr]] ) {
          if ( k >= 0 ) {
            if ( NOR(idx[B[ptr]] - idx[ptr], sz[cur]) != k ) ok = 0;
          } else {
            k = NOR( idx[B[ptr]] - idx[ptr], sz[cur]);
          }
        }
      } while( ptr != i );
      if ( ok ) off[cur] = NOR(k, sz[cur] );
      cur++;
    }
  }

  if ( !ok ) return -1;
  PLL ans = PLL(0, 1);

  REP( i, cn ) {
    PLL tmp;
    ok &= merge( ans, PLL( off[i], sz[i] ), tmp );
    //    printf( "x = %d (%d)\n", off[i], sz[i] );
    ans = tmp;
  }
  if ( !ok ) return -1;
  return ans.first;
}


int n, A[N], B[N];

int main() {
  while( scanf( "%d", &n ), n ) {
    REP( i, n ) {
      scanf( "%d", &A[i] );
      A[i]--;
    } 

    REP( i, n ) {
      scanf( "%d", &B[i] );
      B[i]--;
    }

    LL ans = lg( A, B, n );
    printf( "%lld\n", ans );
  }
  return 0;
}

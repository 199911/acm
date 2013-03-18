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

#define MOD 1000000007

LL exp( LL a, LL b, LL m ) {
  LL ret = 1;
  while( b ) {
    if ( b & 1 ) ( ret *= a ) %= m;
    ( a *= a ) %= m;
    b >>= 1;
  }
  return ret;
}

LL inv( LL a, LL p ) {
  return exp( a, p - 2, p );
}

int rank( LL **A, int m, int n, LL p ) {
  int rnk = 0;
  for( int i = 0, row = 0; i < n && row < m; i++ ) {
    if ( A[row][i] == 0 ) 
      for( int j = row + 1; j < m; j++ ) 
        if ( A[j][i] ) {
          printf( "found\n" );
          for( int k = i; i < n; i++ ) swap( A[row][k], A[j][k] );
          break;
        }
    printf( "%lld\n", A[row][i] );
    if ( A[row][i] ) {
      printf( "haha\n" );
      rnk++;
      LL iv = inv( A[row][i], p );
      for( int j = row + 1; j < m; j++ ) {
        LL mul = iv * A[j][i] % p;
        for( int k = i; k < n; k++ ) {
          A[j][k] -= A[row][k] * mul % p;
          A[j][k] = ( ( A[j][k] % p ) + p ) % p;
        }
      }
      row++;
    }

    for( int i = 0; i < m; i++ ) 
      for( int j = 0; j < n; j++ ) 
        printf( "%10lld%s", A[i][j], j < n - 1 ? " " : "\n" );
    puts( "" );
  }
  for( int i =0; i < m; i++ ) 
    for( int j = 0; j < n; j++ ) 
      printf( "%10lld%s", A[i][j], j < n - 1 ? " " : "\n" );
  puts( "" );
  return rnk;
}

LL** alloc( int m, int n ) {
  LL **ret = ( LL ** ) malloc( m * sizeof( LL ** ) );
  for( int i = 0; i < m; i++ ) {
    ret[i] = ( LL * ) malloc( n * sizeof( LL ) ); 
    for( int j = 0; j < n; j++ ) ret[i][j] = 0;
  }
  return ret;
}

int linear_matroid_intersect( LL **A, LL **B, int m, int n, int r ) {
  LL **C = alloc( m, n );
  LL *rnd = ( LL * ) malloc( r * sizeof( LL ) );
  int ans = -1;

  if ( m > n ) {
    swap( A, B );
    swap( m, n );
  }
  srand( time( NULL ) );
  for( int t = 0; t < 1; t++ ) {
    for( int i = 0; i < r; i++ ) rnd[i] = rand() % MOD;
    for( int i = 0; i < m; i++ ) {
      for( int j = 0; j < n; j++ ) {
        C[i][j] = 0;
        for( int k = 0; k < r; k++ ) 
          ( C[i][j] += A[i][k] * rnd[k] % MOD * B[j][k] % MOD ) %= MOD;
        printf( "%10lld%s", C[i][j], j == n - 1 ? "\n" : " " );
      }
    }
    puts( "" );
    ans = max( ans, rank( C, m, n, MOD ) );
  }
  return ans;
}

int R, r, m, n, k, a[333], b[333], c[333], d[333], srt[1222], mp[11111];
LL **A, **B;

int main() {
  while( scanf( "%d", &R ), R ) {
    k = 0;
    for( int i = 0; i < R; i++ ) {
      scanf( "%d%d%d%d", a + i, b + i, c + i, d + i );
      srt[k++] = a[i];
      srt[k++] = b[i];
      srt[k++] = c[i];
      srt[k++] = d[i];
    }
    sort( srt, srt + k );
    k = unique( srt, srt + k ) - srt;
    for( int i = 0; i < k; i++ ) mp[srt[i]] = i;
    m = R;
    n = k;
    r = 2 * R;
    A = alloc( m, r );
    B = alloc( n, r );

    for( int i = 0; i < R; i++ ) {
      A[i][i * 2] = 1;
      A[i][i * 2 + 1] = 1;
      B[mp[a[i]]][i * 2] = 1;
      B[mp[b[i]]][i * 2] = MOD - 1;
      B[mp[c[i]]][i * 2 + 1] = 1;
      B[mp[d[i]]][i * 2 + 1] = MOD - 1;
    }

    printf( "%d\n", linear_matroid_intersect( A, B, m, n, r ) );
  }
  return 0;
}

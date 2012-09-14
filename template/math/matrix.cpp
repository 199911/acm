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

#define N 200
#define MOD 1000000007

struct M {
  LL A[N][N], n;
  M() {}
  M( int n ): n(n) { CLR( A, 0 ); }

  LL* operator[]( int k ) { return A[k]; }
  M operator+( M B ) {
    M C(n);
    REP( i, n ) REP( j, n ) C[i][j] = ( A[i][j] + B[i][j] ) % MOD;
    return C;
  }
  M operator-( M B ) {
    M C(n);
    REP( i, n ) REP( j, n ) C[i][j] = ( A[i][j] - B[i][j] ) % MOD;
    return C;
  }
  M operator*( M B ) {
    M C(n);
    REP( i, n ) REP( j, n ) {
      C[i][j] = 0;
      REP( k, n ) { 
        C[i][j] += A[i][k] * B[k][j];
        C[i][j] %= MOD;
      }
    }
    return C;
  }

  M pow( LL k ) {
    M res(n), B;
    REP( i, n ) res[i][i] = 1;
    B = *this;
    for( LL x = 1; x <= k; x <<= 1 ) {
      if ( x & k ) res = res * B;
      B = B * B;
    }
    return res;
  }
} A[66];

int toNum( char a ) {
  if ( a >= 'A' && a <= 'Z' ) return a - 'A' + 26;
  if ( a >= 'a' && a <= 'z' ) return a - 'a';
  return 0;
}

int main() {
  LL n;
  int m, k;
  cin >> n >> m >> k;

  M A(m);
  REP( i, m ) REP( j, m ) A[i][j] = 1;

  REP( i, k ) {
    char str[111];
    scanf( "%s", str );
    int a = toNum( str[0] );
    int b = toNum( str[1] );
    A[a][b] = 0;
  }

  if ( n == 1 ) cout << m << endl;
  else {
    M B = A.pow( n - 1 );
    LL ans = 0;
    REP( i, m ) REP( j, m ) {
      ans += B[i][j];
      ans %= MOD;
    }
    cout << ans << endl;
  }

  return 0;
}

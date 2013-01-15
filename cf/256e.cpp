#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

#define LL long long
#define N 100001
#define MOD 777777777

struct Matrix {
  LL a[3][3];
  
  Matrix() { memset( a, 0, sizeof(a)); }
  LL& operator()( int i, int j ) { return a[i][j]; }
  Matrix operator+( Matrix M ) {
    Matrix ret;
    for( int i = 0; i < 3; i++ ) 
      for( int j = 0; j < 3; j++ ) 
        ret( i, j ) = M( i, j ) + a[i][j];
    return ret;
  }

  Matrix operator*( Matrix M ) {
    Matrix ret;
    for( int i = 0; i < 3; i++ ) 
      for( int j = 0; j < 3; j++ ) {
        ret( i, j ) = 0;
        for( int k = 0; k < 3; k++ ) 
          ret( i, j ) += M( i, k ) * (*this)( k, j );
      }
    return ret;
  }
};

LL exp( LL a, LL b ) {
  LL ret = 1;
  while ( b ) {
    if ( b & 1 ) ret *= a, ret %= MOD;
    a *= a, a %= MOD;
    b >>= 1;
  }
  return ret;
}

LL inv( LL a ) {
  return exp( a, MOD - 2 );
}

Matrix dp[N];
int n, m;
int A[N], ans;
set<int> S;

int pred( int x ) {
  set<int>::iterator it = S.lower_bound( x );
  --it;
  return *it;
}

int succ( int x ) {
  set<int>::iterator it = S.upper_bound( x );
  return *it; 
}

int main() {
  scanf( "%d%d", &n, &m );
  for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 3; j++ )
      scanf( "%d", dp[0](i, j) );
  }
  for( int i = 1; i < n; i++ ) dp[i] = dp[i - 1] * dp[0];

  S.clear();
  memset( A, 0, sizeof(A) );

  A[0] = 4;
  S.insert( 0 );
  A[n + 1] = 4;
  S.insert( n + 1 );
  ans = dp[n](4, 4);

  return 0;
}

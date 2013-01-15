#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 111111

int dp[N], a[N], n, m, q[N], k, s[N];

int main() {
  scanf( "%d", &m );
  for( int i = 0; i < m; i++ )
    scanf( "%d", &q[i] );
  scanf( "%d", &n );
  for( int i = 0; i < n; i++ ) 
    scanf( "%d", &a[i] );

  sort( q, q + m );
  sort( a, a + n );

  m = unique( q, q + m ) - q;

  k = 0;
  while ( k < m && q[k] <= q[0] + 2 ) k++;

  s[0] = 0;
  
  for( int i = 1; i <= n; i++ ) { 
    s[i] = s[i - 1] + a[i - 1];
    dp[i] = s[i];
  }

  dp[0] = 0;
  for( int i = 1; i <= n; i++ ) {
    for( int j = 0; j < k; j++ ) {
      if ( q[j] <= i ) {
        int cst = s[i] - s[i - q[j]];
        dp[i] = min( dp[i], cst + dp[i - q[j]] );
        if ( i - q[j] >= 1 ) dp[i] = min( dp[i], cst + dp[i - q[j] - 1] );
        if ( i - q[j] >= 2 ) dp[i] = min( dp[i], cst + dp[i - q[j] - 2] );
      }
    }
//    printf( "dp[%d] = %d\n", i, dp[i] );
  }

  printf( "%d\n", dp[n] );

  return 0;
}

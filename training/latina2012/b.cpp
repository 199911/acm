#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define MOD 1000000007

int s, b, dp[104][205][205], c[309][309];

int doit( int i, int j, int k ) {
  if ( dp[i][j][k] != -1 ) return dp[i][j][k];
  if ( i == 0 ) {
    if ( j < k ) return dp[i][j][k] = 1;
    else return dp[i][j][k] = 0;
  } else {
    if ( j < k ) {
      return dp[i][j][k] = c[j + i][i];
    } else {
      dp[i][j][k] = 0;
      for( int l = 0; l < k; l++ ) {
        dp[i][j][k] += doit( i - 1, j - l, min( 2 * ( k - l ), j - l + 1 ) ); 
        dp[i][j][k] %= MOD;
      }
      return dp[i][j][k];
    }
  }
}

int main() {
  CLR( c, 0 );
  for( int i = 0; i < 305; i++ ) 
    c[i][0] = 1;
  for( int i = 1; i < 305; i++ ) 
    for( int j = 1; j <= i; j++ )
      c[i][j] = ( c[i - 1][j - 1] + c[i - 1][j] ) % MOD;
  CLR( dp, -1 );

  while( scanf( "%d%d", &s, &b ) != EOF ) {
    printf( "%d\n", doit( b - 1, s, 1) );
  }
  return 0;
}

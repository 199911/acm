#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 1111

int k, n, pre[N][N];
LL d[N], w[N], we[N][N], s[N], dp[N][N];

int main() {
  while( scanf( "%d%d", &n, &k ) != EOF ) {
    s[0] = 0;
    for( int i = 1; i <= n; i++ ) { 
      scanf( "%lld%lld", &d[i], &w[i] );
      s[i] = s[i - 1] + w[i];
    }

    for( int i = 1; i <= n; i++ ) we[i][i] = 0;

    for( int l = 2; l <= n; l++ ) 
      for( int i = 1; i <= n - l + 1; i++ ) {
        we[i][i + l - 1] = we[i][i + l - 2] + ( s[i + l - 2] - s[i - 1] ) * ( d[i + l - 1] - d[i + l - 2] );
//        printf( "we[%d, %d] = %d\n", i, i + l - 1, we[i][i + l - 1] );
      }

    for( int i = 1; i <= n; i++ ) 
      dp[i][1] = we[1][i];

    for( int j = 2; j <= k; j++ ) {
      dp[n][j] = 1LL<<60; 
      pre[n][j] = 0;
      for( int i = n - 1; i >= 1; i-- ) {
        if ( dp[n][j] > dp[i][j - 1] + we[i + 1][n] ) {
          dp[n][j] = dp[i][j - 1] + we[i + 1][n];
          pre[n][j] = i;
        } 
      }

      for( int i = n - 1; i >= 1; i-- ) {
        dp[i][j]  = 1LL<<60;
        pre[i][j] = 0;
        for( int x = pre[i][j - 1]; x <= pre[i + 1][j]; x++ ) {
          if ( dp[i][j] > dp[x][j - 1] + we[x + 1][i] ) {
            dp[i][j] = dp[x][j - 1] + we[x + 1][i];
            pre[i][j] = x;
          }
        }
      }
    }

    printf( "%lld\n", dp[n][k] );
  }

  return 0;
}

#include <cstdio>

int main() {
  int n, k;
  scanf( "%d%d", &n, &k );
  long long dp[20][2];
  dp[1][0] = k - 1;
  dp[1][1] = 0;
  for ( int i = 2; i <= n; i++ ) {
    dp[i][0] = ( dp[i - 1][0] + dp[i - 1][1] ) * ( k - 1 );
    dp[i][1] = dp[i - 1][0];
  }

  printf( "%lld\n", dp[n][0] + dp[n][1] );
  return 0;
}

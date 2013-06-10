#include <cstdio>
using namespace std;

int dp[111], k;

int main() {
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 1;
  for( int i = 3; i < 111; i++) {
    dp[i] = dp[i - 2] + dp[i - 3];
  }
  while( scanf( "%d", &k ) != EOF ) {
    printf( "%d\n", dp[k] + dp[k - 1] );
  }
  return 0;
}

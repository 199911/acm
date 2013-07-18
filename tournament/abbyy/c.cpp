#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

int dp[1111111];

int doit( int k ) {
  if ( dp[k] != -1 ) return dp[k];
  
  dp[k] = 1<<29;
  int t = k;
  while( t ) {
    dp[k] = min( doit( k - t % 10 ) + 1, dp[k] );
    t /= 10;
  }
  return dp[k];
}

int main() {
  int x;
  scanf( "%d", &x );
  memset( dp, -1, sizeof( dp ) );
  dp[0] = 0;
  printf( "%d\n", doit( x ) );
  return 0;
}

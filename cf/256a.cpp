#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 4004

int a[N], dp[N][N], n;

int main() {
  scanf( "%d", &n );
  for( int i = 0; i < n; i++ )
    scanf( "%d", &a[i] );
  for( int i = 0; i < n; i++ ) {
    for( int j = 0; j <= i; j++ ) {
      dp[j][i] = 1 + ( j != i );
    }
  }
  int ans = 1;
  for( int i = 0; i < n; i++ ) {
    for( int j = 0, pv = -1; j < i; j++ ) {
      if ( pv != -1 ) dp[j][i] = dp[pv][j] + 1;
      if ( a[j] == a[i] ) pv = j;
      ans = max( ans, dp[j][i] );
    }
  }
  printf( "%d\n", ans );
  return 0;
}

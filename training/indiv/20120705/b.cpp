#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[111][111][111];

int dfs(int a, int b, int c) {
  if( dp[a][b][c] != -1 ) return dp[a][b][c];

  if( a < c ) return dp[a][b][c] = 0;
  if( b * c < a ) return dp[a][b][c] = 0;
  if( a == 0 || c == 0 ) return dp[a][b][c] = 0;
  if( c == 1 ){
    return dp[a][b][c] = 1;
  }

  int ans = 0;

  for(int i = 1; i <= min(a, b); i++) {
    ans += dfs(a - i, i, c - 1);
  }

  return dp[a][b][c] = ans;
}


int main(){
  int cas, n, m;
  memset(dp, -1, sizeof(dp));
  scanf( "%d", &cas );
  while( cas-- ) {
    scanf( "%d%d", &n, &m );
    int ans = 0;
    for(int i = 1; i <= m; i++) ans += dfs(n, n ,i);
    printf("%d\n", ans);
  }

  return 0;
}

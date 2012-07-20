#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
  char s[2222], t[2222];
  int dp[2][2222];
  int n, m;

  while( scanf( "%s%s", s, t ) != EOF ) {
    memset(dp, 0, sizeof(dp));
    n = strlen(s);
    m = strlen(t);
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= m; j++ ) {
        dp[i%2][j] = max(dp[(i-1)%2][j-1] + (s[i-1] == t[j-1]), max(dp[i%2][j-1], dp[(i-1)%2][j]));
      }
    }
    printf("%d\n", dp[n%2][m]);
  }

  return 0;
}

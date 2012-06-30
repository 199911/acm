#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int cbit[1<<15], flg[1002], dp[2][1<<15], di[1001], n,d,  k, ans;

int main(){
  memset(dp, -1, sizeof(dp));
  memset(flg, 0, sizeof(flg));
  memset(cbit, 0, sizeof(cbit));
  scanf("%d%d%d", &n, &d, &k);
  for(int i = 0; i < n; i++) {
    scanf("%d", &di[i]);
    for(int j = 0; j < di[i]; j++) {
      int x;
      scanf("%d", &x);
      x--;
      flg[i] |= 1 << x;
    }
  }

  for(int i = 0; i < 1<<15; i++) {
    for(int j = 0; j < 15; j++) {
      if( i & 1 << j) cbit[i]++;
    }
  }


  ans = 0;
  dp[0][0] = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 1<<d; j++ ) {
//      printf("%d %d %d\n", i, j, dp[i][j]);
      if(dp[i%2][j] != -1) {
        dp[(i+1)%2][j] = max(dp[(i+1)%2][j], dp[(i)%2][j]);
        dp[(i+1)%2][j|flg[i]] = max(dp[(i+1)%2][j|flg[i]], dp[(i)%2][j] + 1);
        if(cbit[j|flg[i]] <= k ) ans = max(ans, dp[(i+1)%2][j|flg[i]]);
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}

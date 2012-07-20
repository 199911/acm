#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define LL long long

LL c[222][222];
int n, m, vis[222];

LL dfs(int x, LL f ) {
  vis[x] = 1;
  if ( x == n - 1 ) {
    return f;
  } else {
    for(int y = 0; y < n; y++ ) {
      LL tt;
      if (c[x][y] > 0 && !vis[y] && (tt = dfs(y, min(c[x][y], f)))) {
        c[x][y] -= tt;
        c[y][x] += tt;
        return tt;
      }
    }
  }
  return 0LL;
}

int main(){
  while( scanf( "%d%d", &m, &n ) != EOF ) {
    memset(c, 0, sizeof(c));
    for(int i = 0; i < m; i++) {
      int a, b; 
      LL d;
      scanf( "%d%d%lld", &a, &b, &d );
      a--; b--;
      c[a][b] += d;
    }

    LL ans = 0, f = 0;

    memset(vis, 0, sizeof(vis));
    while( f = dfs( 0, 1LL<<40 ) ) {
      ans += f;
      memset(vis, 0, sizeof(vis));
    }
    printf("%lld\n", ans);
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 111
#define INF (1<<29)

int adj[N][N], n, m, dist[N], et, blk;
int q[N], qt, qh;

void bfs( int s ) {
  qh = qt = 0;
  q[qt++] = s;
  dist[s] = 0;
  for( int i = 0; i < n; i++ ) dist[i] = INF;
  while( qt > qh ) {
    int w = q[qh++];
    for( int v = 0; v < n; v++ ) {
      if ( adj[v][w] && dist[v] == INF ) {
        dist[v] = dist[w] + 1;
        q[qt++] = v;
      }
    }
  }
}

int vis[N];
void dfs( int x ) {
  if ( x == blk ) return;
  vis[x] = 1;
  for( int y = 0; y < n; y++ ) {
    if ( adj[x][y] && !vis[y] ) 
      dfs( y );
  }
}

int main() {
  scanf( "%d%d", &n, &et ); 
  memset( adj, 0, sizeof( adj ) );
  int a, b;
  while( scanf( "%d%d", &a, &b ) != EOF ) {
    adj[a][b] = 1;
  }
  for( int i = 0; i < n; i++ ) dist[i] = INF;
  bfs( et );
  int ans = 0;
  for( blk = 1; blk < n; blk++ ) {
    if ( blk == et ) continue;
    memset( vis, 0, sizeof( vis ) );
    dfs( 0 );
    if ( !vis[et] ) {
      if ( dist[ans] > dist[blk] ) ans = blk;
    }
  }
  printf( "Put guards in room %d.\n", ans );
  return 0;
}

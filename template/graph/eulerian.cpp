#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

// find the lex smallest (in terms of vertices) euler cycle

#define N 111
#define M 111111

// graph in adj list
int adj[N][N], cur[N], n, m;
int hd, nt[M], vtx[M], cnt;

void init() {
  memset(adj, 0, sizeof(adj));
  memset(cur, 0, sizeof(cur));
  hd = -1;
  memset(nt, -1, sizeof(nt));
  cnt = 0;
}

void push( int x ) {
  nt[cnt] = hd;
  vtx[cnt] = x;
  hd = cnt++;
}

void dfs(int x) {
  for (int &v = cur[x]; v < n; v++) {
    if ( adj[x][v] > 0 ) {
      adj[x][v]--;
      if ( x != v ) adj[v][x]--;
      dfs( v );
      push( x );
    }
  }
}

int main() {
  scanf( "%d%d", &n, &m );
  init();
  REP(i, m) {
    int a, b;
    scanf( "%d%d", &a, &b );
    adj[a][b] = adj[b][a] = 1;
  }
  push(0);
  dfs(0);
  for( int e = hd; e != -1; e = nt[e] ) printf( "%d\n", vtx[e] );
	return 0;
}

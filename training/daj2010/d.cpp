#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 
#define ABS(a) ((a)<0?-(a):(a))

#define N 2222
#define M 2222222

int hd[N], nt[M], to[M], en, rhd[N], rnt[M], rto[M], ren;
int adj[N][N], n, x[N], y[N], d[N], T;
int cnt[N], scc[N], sccn, ln, l[N], vis[N];

void init() {
  CLR( rhd, -1 );
  CLR( hd, -1 );
  en = ren = 0;
}

void add( int a, int b ) {
//  printf( "add %d %d\n", a + 1, b + 1 );
  to[en] = b; nt[en] = hd[a]; hd[a] = en++;
  rto[ren] = a; rnt[ren] = rhd[b]; rhd[b] = ren++;
}

void dfs( int x ) {
  vis[x] = 1;
//  printf( "vis %d\n", x );
  /*
  REP( y, n ) {
    if ( adj[x][y] && !vis[y] ) {
      dfs( y );
    }
  }
  */
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    if( !vis[to[e]] ) dfs( to[e] );
  }
  l[ln--] = x;
}

void dfs2( int  x ){
//  printf( "rvis %d %d\n", x, sccn );
  vis[x] = 1;
  scc[x] = sccn;
  for( int e = rhd[x]; e != -1; e = rnt[e] ) {
    if ( !vis[rto[e]] ) dfs2( rto[e] );
  }
  /*
  REP( y , n ) {
    if ( adj[y][x] && !vis[y] ) {
      dfs2( y );
    }
  }
  */
}

int solve() {
  ln = n - 1;
  CLR( vis, 0 );
  REP( i, n ) {
    if( !vis[i] ) dfs( i );
  }

  int ret = 0;
  CLR( vis, 0 );
  sccn = 0;
  REP( i, n ) {
    if( !vis[l[i]] ) {
      dfs2( l[i] );
      sccn++;
    }
  }


  CLR( cnt, 0 );
//  printf( "sccn = %d\n", sccn );
  REP( x, n ) {
    for( int e = hd[x]; e != -1; e = nt[e] ) {
      int y = to[e];
      if ( scc[x] != scc[y] ) { 
//        printf( "%d => %d\n", scc[x], scc[y] );
        cnt[scc[y]]++;
      }
    }
  }

  REP( i, sccn ) 
    if ( cnt[i] == 0 ) ret++;

  return ret;
}

int main() {
  scanf( "%d", &T );
  while( T-- ) {
    scanf( "%d", &n );
    REP( i, n ) scanf( "%d%d%d", &x[i], &y[i], &d[i] );
    init();
    REP( i, n ) {
//      adj[i][i] = 0;
      FOR( j, i + 1, n ) {
        int dist = max( ABS(x[i]-x[j]), ABS(y[i] - y[j]));
//        adj[i][j] = 2 * dist <= d[i];
//        adj[j][i] = 2 * dist <= d[j];
//        if ( adj[i][j] ) printf( "%d => %d\n", i + 1, j + 1);
//        if ( adj[j][i] ) printf( "%d => %d\n", j + 1, i + 1);
        if ( 2 * dist <= d[i] ) add( i, j );
        if ( 2 * dist <= d[j] ) add( j, i );
      }
    }

    printf( "%d\n", solve() );
  }

  return 0;
}

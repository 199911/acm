#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }
#define EPS (1e-11)

double A [111][111];
int piv[111];

void ge( int m, int n ) {
  /*
  REP( i, m ) { 
    REP( j, n ) 
      printf( "%f ", A[i][j] );
    puts( "" );
  }
  */
  for( int i = 0, cur = 0; i < n; i++ ) {
    if ( fabs( A[cur][i] ) > EPS ) {
      piv[i] = cur;
    } else {
      piv[i] = -1;
      for( int j = cur + 1; j < m; j++ ) {
        if ( fabs( A[j][i] ) > EPS ) {
          piv[i] = cur;
          for( int k = 0; k < n; k++ ) 
            swap( A[j][k], A[cur][k] );
          break;
        }
      }
    }

    if ( piv[i] == -1 ) continue;


    for( int k = n - 1; k >= i; k-- ) 
      A[cur][k] /= A[cur][i];
    for( int j = cur + 1; j < m; j++ ) {
      double t = A[j][i] / A[cur][i];
      for( int k = i; k < n; k++ ) 
        A[j][k] -= A[cur][k] * t;
    }

    cur++;
  }
  /*
  REP( i, m ) { 
    REP( j, n ) 
      printf( "%f ", A[i][j] );
    puts( "" );
  }
  */

}

void bs( int m, int n ) {
  for( int i = m - 1; i > 0; i-- ) {
    if ( piv[i] == -1 ) continue;
    int cur = piv[i];
    for( int j = cur - 1; j >= 0; j-- ) {
      double rat = A[j][i] / A[cur][i];
      for( int k = i; k < n; k++ ) 
        A[j][k] -= A[cur][k] * rat;
    }
  }
}

int outdg[111], n; 

int fl[111], vis[111], adj[111][111], scc[111], sn, l[111], ln, snk[111], ext[111];
int inf[111], zr[111];

void dfs1( int v ) {
  vis[v] = 1;
  for( int i = 0; i < n; i++ ) {
    if ( adj[v][i] && !vis[i] )  dfs1( i );
  }
  l[--ln] = v;
}

void dfs2( int x ) {
  vis[x] = 1;
  scc[x] = sn;
  REP( i, n ) 
    if ( adj[i][x] && !vis[i] ) dfs2(i);
}

void find_scc() {
  CLR( vis, 0 );
  CLR( scc, -1 );
  ln = n; sn = 0;
  REP( i, n ) 
    if( !vis[i] ) 
      dfs1(i);
  CLR( vis, 0 );
  REP( i, n ) {
    if ( !vis[l[i]] ) {
      dfs2( l[i] );
      sn++;
    }
  }
}

void dfs( int x ) {
  vis[x] = 1;
  REP( y, n ) if ( adj[x][y] && !vis[y] ) dfs( y );
}

int main() {
  int cas = 1;
  while( scanf( "%d", &n ), n )  {
    memset( outdg, 0, sizeof( outdg ) );
    for( int i = 0; i <= n; i++ ) 
      for( int j = 0; j <= n; j++ ) 
        A[i][j] = 0;
    CLR( adj, 0 );

    int a, b;
    while( scanf( "%d%d", &a, &b ), a || b ) {
      a--; b--;
      A[b][a] += 1.0;
      adj[a][b] = 1;
      outdg[a]++;
    }
    for( int i = 0; i < n; i++ ) 
      for( int j = 0; j < n; j++ ) 
        if ( outdg[j] ) 
          A[i][j] /= outdg[j];
    for( int i = 0; i < n; i++ ) A[i][i] -= 1.0;
    A[0][n] = -1.0;

    /*
    REP( i, n ) {
      REP( j, n + 1 ) {
        printf( "%.3f ", A[i][j] );
      }
      puts( "" );
    }
    */
    
    ge( n, n + 1 );
    bs( n, n + 1 );

    find_scc();
    CLR( vis, 0 );
    REP( i, sn ) snk[i] = 1, ext[i] = 0;
    REP( i, n ) REP( j, n ) 
      if ( adj[i][j] && scc[i] != scc[j] ) snk[scc[i]] = 0;
    REP( i, n ) if ( outdg[i] == 0 ) ext[scc[i]] = 1;
//    REP( i, n ) printf( "scc[%d] = %d(%d, %d)\n", i, scc[i], snk[scc[i]], ext[scc[i]] );
    dfs(0);

    printf( "Case #%d:\n", cas++ );
    int q, tmp;
    scanf( "%d", &q );
    REP( i, q ) { 
      scanf( "%d", &tmp );
      tmp--;
      if ( !vis[tmp] ) puts( "0.000" );
      else if ( snk[scc[tmp]] && !ext[scc[tmp]] ) puts( "infinity" );
      else if( piv[tmp] != -1 ) printf( "%.3f\n", A[piv[tmp]][n] + EPS );
      else while(1);
    }
  }

  return 0;
}

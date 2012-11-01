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

#define N 222

bool adj[N][N];
int n;

int p[N], m[N], d[N], c1[N], c2[N];
int q[N], qt, qh;

int pp[N];

int f( int x ) { return pp[x] == x ? x : ( pp[x] = f( pp[x] )); } 
void u( int x, int y ) { pp[x] = y; }

void path( int r, int x ) {
  if ( r == x ) return;

  if ( d[x] == 0 ) {
    path( r, p[p[x]] );
    int i = p[x], j = p[p[x]];
    m[i] = j; m[j] = i;
  } else if ( d[x] == 1 ) {
    path( m[x], c1[x] );
    path( r, c2[x] );
    int i = c1[x], j = c2[x];
    m[i] = j; m[j] = i;
  }
}

int v[N];
int lca( int x, int y, int r ) {
  int i = f( x ), j = f( y );
  while( i != j && v[i] != 2 && v[j] != 1 ) {
    v[i] = 1; v[j] = 2;
    if ( i != r ) i = f( p[i] );
    if ( j != r ) j = f( p[j] );
  }

  int b = i, z = j; if ( v[j] == 1 )  swap( b, z );
  
  for ( int i = b; i != z; i = f( p[i] ) ) v[i] = -1;
  v[z] = -1; 

  return b;
}

void shrink_one_side( int x, int y, int b ) {
  for( int i = f( x ); i != b; i = f( p[i] ) ) {
    u( i, b );
    if ( d[i] == 1 ) {
      c1[i] = x;
      c2[i] = y;
      q[qt++] = i;
    }
  }
}

int bfs( int r ) {
  REP( i, n ) pp[i] = i;
  memset( v, -1, sizeof( v ));
  memset( d, -1, sizeof( d ));
  d[r] = 0;

  qh = qt = 0;
  q[qt++] = r;

  while ( qt > qh ) {
    for( int x = q[qh++], y = 0; y < n; y++ ) {
      if ( adj[x][y] && m[y] != y && f(x) != f(y) ) {
        if ( d[y] == -1 ) {
          if ( m[y] == -1 ) {
            path( r, x );
            m[x] = y; m[y] = x;
            return 1;
          } else {
            p[y] = x; p[m[y]] = y;
            d[y] = 1; d[m[y]] = 0;
            q[qt++] = m[y];
          }
        } else {
          if ( d[f(y)] == 0 ) {
            int b = lca( x, y, r );
            shrink_one_side( x, y, b );
            shrink_one_side( y, x, b );
          }
        }
      }
    }
  }

  return 0;
}

int GeneralMatch() {
  memset( m, -1, sizeof( m ) );
  int ans = 0;
  for( int i = 0; i < n; i++ ) 
    if ( m[i] == -1 ) ans += bfs( i );
  return ans;
}

int main() {
  memset( adj, 0, sizeof( adj ) );
  scanf( "%d", &n );
  int a, b;
  while( scanf( "%d%d", &a, &b ) != EOF ) {
    if ( a == b ) continue;
    a--; b--;
    adj[a][b] = adj[b][a] = 1;
  }
  GeneralMatch();
  int cnt = 0;
  for( int i = 0; i < n; i++ ) if ( m[i] != -1 && m[i] != i ) cnt++;
  printf( "%d\n", cnt );
  for( int i = 0; i < n; i++ ) {
    if ( m[i] != -1 && i < m[i] ) printf( "%d %d\n", i + 1, m[i] + 1 );
  }
  return 0;
}

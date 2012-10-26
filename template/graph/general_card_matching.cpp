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

#define N 101

bool adj[N][N];
int p[N], m[N], d[N], c1[N], c2[N];
int q[N], qt, qh;

int pp[N];

void init( int n ) { REP( i, n ) pp[i] = i; }
int f( int x ) { return pp[i] == i ? i : ( pp[i] = f( pp[i] )); } 
void u( int x, int u ) { pp[f( x )] = f( y ); }

void path( int r, int x ) {
  if ( r == x ) return;

  if ( d[x] == 0 ) {
    path( r, p[p[x]] );
    int i = p[x], j = pp[x];
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
    v[i] =  1; v[j] = 2;
    if ( i != r ) i = f( p[i] );
    if ( j != r ) j = f( p[j] );
  }

  int b = i, z = j; if ( v[j] == 1 )  swap( b, z );
  
  for ( int i = b; i != z; i = f( p[i] ) ) v[i] = -1;
  v[z] = -1; 
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

bool bfs( int r ) {
  REP( i, n ) pp[i] = i;
  CLR( v, -1 );
  CLR( d, -1 );
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
            return true;
          } else {

          }
        }
      }
    }
  }
}

int main() {
  return 0;
}

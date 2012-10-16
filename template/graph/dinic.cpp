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

// graph structure
#define N 4444
#define M 222222

int hd[N], nt[M], to[M], en, n, m;
LL cap[M];

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
}

void add( int a, int b, int c ) {
  cap[en] = c; to[en] = b; nt[en] = hd[a]; hd[a] = en++;
  cap[en] = c; to[en] = a; nt[en] = hd[b]; hd[b] = en++;
}

int cur[N], d[N], f[M], vis[N], flow, s, t;

bool bfs( int s ) {
  CLR( d, -1 ); 
  d[s] = 0;
  int q[N], qt, qh;
  qt = qh = 0;
  q[qt++] = s;
  
  while( qt > qh ) {
    int w = q[qh++];
    for( int e = hd[w]; e != -1; e = nt[e] ) 
      if ( d[to[e]] < 0 && cap[e] > 0) {
        d[to[e]] = d[w] + 1;
        q[qt++] = to[e];
      }
  }
  return d[t] >= 0;
}

LL dfs( int w, LL f ) {
  LL ret = 0;
  if ( w == t ) return f;
  for( int &e = cur[w]; e != -1; e = nt[e] ) {
    if ( cap[e] > 0 && d[to[e]] == d[w] + 1 && !vis[to[e]] && ( ret = dfs( to[e], min( f, cap[e] ) ) ) ){
      cap[e] -= ret;
      cap[e^1] += ret;
      return ret;
    } 
  }
  return 0;
}

LL dinic() {
  LL ret = 0;
  CLR( f, 0 );
  while( bfs( s ) ) {
    LL nf = 0;
    while( CLR( vis, 0 ), copy( hd, hd + n, cur), nf = dfs( s, 1LL<<62 ) ) 
      ret += nf;
  }
  return ret;
}

int main() {
  int cas = 1;
  while( scanf( "%d", &n ), n ) {
    init();
    scanf( "%d%d%d", &s, &t, &m );
    s--; t--;
    REP( i , m ) {
      int a, b, c;
      scanf( "%d%d%d", &a, &b, &c );
      a--; b--;
      add( a, b, c );
    }
    LL ans = dinic();
    printf( "Network %d\nThe bandwidth is %lld.\n\n", cas++, ans );
  }
  return 0;
}

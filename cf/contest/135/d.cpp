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
#include <map>
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

#define N 555555

int hd[N], nt[N], to[N], en, n;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; hd[a] = en++; 
  to[en] = a; nt[en] = hd[b]; hd[b] = en++; 
}

int vis1[N];

int dfs1( int x ) {
  int ans = 0;
  vis1[x] = 1;
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    int y = to[e];
    if ( !vis1[y] ) {
      ans += dfs1( y );
      ans += e & 1;
    }
  }
  return ans;
}

int vis2[N], mi[N];

void dfs2( int x, int cur ) {
  mi[x] = cur;
  vis2[x] = 1;
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    int y = to[e];
    if ( !vis2[y] ) {
      dfs2( y, cur + ( e & 1 ? -1 : 1 )); 
    }
  }
}

int main() {
  cin >> n;
  init();
  REP( i, n - 1) {
    int a, b;
    scanf( "%d%d", &a, &b );
    a--; b--;
    add( a, b );
  }
  CLR( vis1, 0 );
  CLR( vis2, 0 );
  int cur = dfs1( 0 );
  dfs2( 0, cur );

  int ans = 1<<29, cnt = 0;
  REP( i, n ) ans = min( ans, mi[i] );
  REP( i, n ) if ( ans == mi[i] ) cnt++;
  printf( "%d\n", ans );
  REP( i, n ) if ( ans == mi[i] ) printf( "%d%s", i + 1, --cnt ? " " : "\n" );
  return 0;
}

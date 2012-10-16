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

#define N 5555
#define M 111111

int hd[N], nt[M], to[M], wt[M], en, n;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
}

void add( int a, int b, int c ) {
  to[en] = b; nt[en] = hd[a]; wt[en] = c; hd[a] = en++;
}

int d[N], p[N];

void dijkstra( int s ) {
  CLR( p, -1 );
  REP( i, n ) d[i] = INF;
  multimap<int,int> pq;

  pq.insert( PII(0, s) );
  d[s] = 0;

  while( !pq.empty() ) {
    multimap<int,int>::iterator it = pq.begin();
    int dst = it->first, v = it->second;
    pq.erase( it );

    if ( dst == d[v] ) {
      for( int e = hd[v]; e != -1; e = nt[e] ) {
        int w = to[e];

        if ( d[w] > d[v] + wt[e] ) {
          d[w] = d[v] + wt[e];
          p[v] = w;
          pq.insert( PII( d[w], w ) );
        }
      }
    }
  }
}

int main() {
  int m, k, T[12];

  while( scanf( "%d%d", &m, &k ) != EOF ) {
    init();
    n = 100 * m + 1;
    REP( i, m ) scanf( "%d", &T[i] );
    getchar();

    REP( i, m ) REP( j, m ) if ( i != j ) {
      REP( k, 100 ) add( k + i * 100, k + j * 100, 60 );
    }
    REP( i, m ) {
      string line;
      getline( cin, line );
      istringstream ISS(line);
      
      int lst, cur;
      ISS >> lst;

      while( ISS >> cur ) {
        add( cur + 100 * i, lst + 100 * i, (cur - lst) * T[i] );
        add( lst + 100 * i, cur + 100 * i, (cur - lst) * T[i] );
        lst = cur;
      }
    } 

    REP( i, m ) add( n - 1, 100 * i, 0 );
    dijkstra( n - 1 );

    int ans = INF;
    REP( i, m ) ans = min( ans, d[k + i * 100] );
    if ( ans < INF ) printf( "%d\n", ans );
    else puts( "IMPOSSIBLE" );
  }

  return 0;
}

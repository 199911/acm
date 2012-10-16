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

#define N 444
#define M 22222

int hd[N], nt[M], to[M], cp[M], en, n;
LL ct[M];

void init() {
  CLR( cp, 0 );
  CLR( ct, 0 );
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
}

void add( int a, int b, int c, LL d ) {
  to[en] = b; nt[en] = hd[a]; cp[en] = c; ct[en] = d; hd[a] = en++;
  to[en] = a; nt[en] = hd[b]; cp[en] = 0; ct[en] = -d; hd[b] = en++;
}

// successive shortest path using spfa

pair<int,LL> ssp( int s, int t ) {
  int q[N], inq[N], qh, qt;
  int pv[N], pe[N], flow;
  LL cost, d[N];
  flow = 0;
  cost = 0;

  while ( true ) {
    qh = qt = 0;
    CLR( inq, 0 );
    REP( i, n ) d[i] = 1LL << 60;

    d[s] = 0;
    q[qt++] = s;
    inq[s] = 1;

    while ( qt != qh ) {
      int w = q[qh++]; qh %= N;
      inq[w] = 0; 

      for( int e = hd[w]; e != -1; e = nt[e] ) {
        if ( cp[e] ) {
          int v = to[e];
          if ( d[v] > d[w] + ct[e] ) {
            d[v] = d[w] + ct[e];
            pe[v] = e;
            pv[v] = w;
            if ( inq[v] == 0 ) {
              q[qt++] = v; qt %= N;
              inq[v] = 1;
            }
          }
        }
      }
    }

    if ( d[t] >= 1LL << 60 ) break; 

    int nf = INF; 
    for( int ptr = t; ptr != s; ptr = pv[ptr] ) 
      nf = min( nf, cp[pe[ptr]] );
    for( int ptr = t; ptr != s; ptr = pv[ptr] ) {
      cp[pe[ptr]] -= nf;
      cp[pe[ptr] ^ 1] += nf;
    }

    if ( nf >= INF ) while ( 1 );
    flow += nf;
    cost += d[t] * nf;
  } 

  return pair<int,LL>(flow, cost);
}

int m, K, D, u[M], v[M];
LL y[M];

int main() {
  while( scanf( "%d%d", &n, &m ) != EOF ) {
    init();
    REP( i, m ) scanf( "%d%d%lld", &u[i], &v[i], &y[i] );
    scanf( "%d%d", &D, &K );
    int s = 0, t = n;
    REP( i, m ) { 
      add( u[i], v[i], K, y[i] );
      add( v[i], u[i], K, y[i] );
    }
    n++;
    add( s, 1, D, 0 );
    pair<int,LL> ans = ssp( s, t );

    if ( ans.first != D ) printf( "Impossible.\n" );
    else printf( "%lld\n", ans.second );
  } 
  return 0;
}


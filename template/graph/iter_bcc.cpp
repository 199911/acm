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

#define N 100005
#define M 200005

int hd[N], nt[M], to[M], en;
int n, m;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; hd[a] = en++;
  to[en] = a; nt[en] = hd[b]; hd[b] = en++;
}

// iterative dfs - compute low
int DFS[N], cur[N], pi[N], low[N], idx[N], dn;

void dfs() {
  int tm = 1;
  CLR( idx, 0 );
  CLR( pi, -1 );
  REP( i, n ) cur[i] = hd[i];

  REP( s, n ) {
    if ( idx[s] == 0 ) {
      dn = 0;
      DFS[dn++] = s;

      while( dn > 0 ) {
        int w = DFS[dn - 1];
        if ( idx[w] == 0 ) low[w] = idx[w] = tm++;
        for( int &e = cur[w]; e != -1 && idx[to[e]]; e = nt[e] ) 
          if ( to[e] != pi[w] ) 
            low[w] = min( low[w], idx[to[e]] );
        if ( cur[w] == -1 ) {
          if ( pi[w] != -1 ) 
            low[pi[w]] = min( low[pi[w]], low[w] );
          dn--;
        } else if ( !idx[to[cur[w]]] ){
          int v = to[cur[w]];
          pi[v] = w;
          DFS[dn++] = v;
        }
      }
    }
  }
}

int bc[M], vis[N], CC[N], bv[M], nbc;
map<int, int> MP[N];
int ok[N];

void bcc() {
  CLR( vis, 0 );
  CLR( bc, -1 );
  REP( i, n ) cur[i] = hd[i];
  nbc = 0;

  REP( s, n ) {
    if ( !vis[s] ) {
      dn = 0;
      CC[dn] = nbc++;
      ok[nbc - 1] = 1;
      DFS[dn++] = s;
      MP[nbc - 1].insert( s, 0 );

      while( dn > 0 ) {
        int u = DFS[dn - 1], cc = CC[dn - 1];
        int par = *MP[cc].find(u);
        if ( !vis[u] ) vis[u] = 1;
        for( int &e = cur[u]; e != -1 && vis[to[e]] == 1; e = nt[e] ) { 
          if ( bc[e ^ 1] == -1 ) { 
            bc[e] = cc;
          }
        }

        if ( cur[u] == -1 ) {
          dn--;
        } else if ( vis[to[cur[u]]] == 0 ) {
          int v = to[cur[u]];
          if ( u == s && idx[v] != idx[u] + 1 || u != s && low[v] >= idx[u] ) {
            bv[nbc] = u;
            bc[cur[u]] = nbc;
            CC[dn] = nbc++;
            ok[nbc - 1] = 1;
            DFS[dn++] = u;
          } else {
            bc[cur[u]] = cc;
            CC[dn] = cc;
            DFS[dn++] = u;
          }
        }
      }
    }
  }
}

int main() {
  int T;
  scanf( "%d", &T );
  while( T-- ) {
    scanf( "%d%d", &n, &m );
    init();
    REP( i, m ) {
      int a, b;
      scanf( "%d%d", &a, &b );
      a--; b--;
      add( a, b );
    }
  }
  return 0;
}

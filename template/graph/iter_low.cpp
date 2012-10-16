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

#define N 200
#define M 20000

int hd[N], nt[M], to[M], en;
int n;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; hd[a] = en++;
  to[en] = a; nt[en] = hd[b]; hd[b] = en++;
}

// iterative dfs
int DFS[N], cur[N], pi[N], low[N], idx[N], dn;

void dfs( int s ) {
  int tm = 1;
  dn = 0;
  DFS[dn++] = s;
  CLR( idx, 0 );
  CLR( pi, -1 );
  REP( i, n ) cur[i] = hd[i];

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

int ap[N], an;

void find_ap() {
  an = 0;
  REP( i , n ) { 
    if ( pi[i] == -1 ) {
      int cnt = 0;
      REP( j , n ) if ( pi[j] == i ) cnt++;
      if ( cnt > 1 ) ap[an++] = i;
    } else {
      int ok = 1;
      for( int e = hd[i]; e != -1; e = nt[e] ) 
        if ( pi[to[e]] == i && low[to[e]] >= idx[i] ) ok = 0;
      if ( !ok ) ap[an++] = i;
    }
  }
}

int main() {
  while( scanf( "%d", &n ), n ) {
    getchar();
    init();
    while( 1 ) {
      string line;
      getline( cin, line );
      istringstream iss(line);

      int a, b;
      iss >> a;
      if ( a == 0 )  {
        break;
      } else {
        while( iss >> b ) 
          add( a - 1, b - 1 );
      }
    }
    dfs(0);
    find_ap();
    printf( "%d\n", an );
  }
  return 0;
}

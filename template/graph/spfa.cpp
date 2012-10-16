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

#define N 5555
#define M 111111

int hd[N], nt[M], to[M], wt[M], en, n, m;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
}

void add( int a, int b, int c ) {
  to[en] = b; nt[en] = hd[a]; wt[en] = c; hd[a] = en++;
}

int d[N], q[N], qh, qt, qc[N], fl[N], p[N];

bool spfa( int s ) {
  qh = qt = 0;
  CLR( qc, 0 );
  REP( i, n ) d[i] = INF;
  CLR( f, 0 );

  q[qt++] = s;
  d[s] = 0;
  qc[s]++;
  fl[s] = 1;

  while( qt > qh ) {
    int w = q[qh++];
    fl[w] = 0;
    for( int e = hd[w]; e != -1; e = nt[e] ) {
      int v = to[e];
      if ( d[w] + wt[w] < d[v] ) {
        d[v] = d[w] + wt[w];
        if ( fl[v] == 0 ) {
          p[v] = w;
          q[qt++] = v;
          qc[v]++;
          fl[v] = 1;
          if ( qc[v] > n ) return false;
        }
      }
    }
  }

  return true;
}


int main() {
  return 0;
}

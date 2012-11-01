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

#define N 555

LL g[N][N];
int v[N], a[N];
LL w[N];
int n, m;

LL GlobalMinCut() {
  for( int i = 0; i < n; i++ ) v[i] = i;
  int k = n;
  LL ans = 1LL << 62;

  while( k > 1 ) {
    a[v[0]] = 1;
    for( int i = 1; i < k; i++ ) {
      a[v[i]] = 0;
      w[i] = g[v[0]][v[i]];
    }
    int p = v[0];
    for( int i = 1; i < k; i++ ) {
      int l = -1;
      for( int j = 1; j < k; j++ ) 
        if ( !a[v[j]] && ( l < 0 || w[j] > w[l] ) ) l = j;
      a[v[l]] = 1;
      if( i == k - 1 ) {
        ans = min( ans, w[l] );
        for( int i = 0; i < k; i++ ) 
          g[v[i]][p] = g[p][v[i]] += g[v[l]][v[i]];
        v[l] = v[--k];
        break;
      }
      p = v[l];
      for( int j = 1; j < k; j++ ) 
        if ( !a[v[j]] ) 
          w[j] += g[v[l]][v[j]];
    }
  }

  return ans;
}

int main() {
  while( scanf( "%d%d", &n, &m ) != EOF ) {
    memset( g, 0, sizeof( g ) );
    for( int i = 0; i < m; i++ ) {
      int a, b;
      LL c;
      scanf( "%d%d%lld", &a, &b, &c );
      g[a][b] += c;
      g[b][a] += c;
    }
    printf( "%lld\n", GlobalMinCut() );
  }
  return 0;
}

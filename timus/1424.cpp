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

#define K 50003
#define N 100004

int n, m, k, p;
int s[K], t[K], A[K * 2], u = 0;
LL ans = 0;

bool comp( const int &a, const int &b ) {
  return t[a] < t[b] || t[a] == t[b] && s[a] < s[b];
}

int main() {
  scanf( "%d%d%d%d", &n, &m, &k, &p );
  REP( i, k ) { 
    scanf( "%d%d", &s[i], &t[i] );
    A[u++] = s[i];
    A[u++] = t[i];
  }
  sort( A, A + u );
  u = unique( A, A + u ) - A;

  REP( i, k ) {
    s[i] = lower_bound( A, A + u, s[i] ) - A;
    t[i] = lower_bound( A, A + u, t[i] ) - A;
  }

  REP( i, k ) A[i] = i;
  sort( A, A + k, comp );

  int ans = 0, L[K];
  multiset<int, greater<int> > S;

  REP( i, m ) S.insert( 0 );

  REP( i, k ) {
    int x = A[i];
    multiset<int, greater<int> >::iterator it = S.lower_bound( s[x] );
    if ( it != S.end() ) {
      L[ans++] = x;
      S.erase( it );
      S.insert( t[x] );
    } 
  }

  printf( "%d\n", ans * p );
  REP( i, ans ) { 
    printf( "%d", L[i] + 1 );
    if ( i == ans - 1) puts( "" );
    else printf( " " );
  }

  return 0;
}

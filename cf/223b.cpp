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
#include <bitset>
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

#define N 222222

int d[N], e[N], f[300], l[300], n, m;
char s[N], t[N];

int main() {
  scanf( "%s%s", s, t );
  n = strlen( s );
  m = strlen( t );

  for( int i = 0, p = 0; i < n; i++ ) {
    if ( p < m && s[i] == t[p] ) p++;
    d[i] = p;
  }

  for( int i = n - 1, p = 0; i >= 0; i-- ) {
    if ( p < m && s[i] == t[m - 1 - p] ) p++;
    e[i] = p;
  }

  memset( f, -1, sizeof( f ) );
  memset( l, -1, sizeof( l ) );

  for( int i = 0; i < m; i++ ) {
    if ( f[t[i]] == -1 ) f[t[i] - 'a'] = i; 
    l[t[i]] = i;
  }

  int ok = 1;

  for( int i = 0; i < n; i++ ) { 
    if ( f[t[i]] == -1 || l[t[i]] == -1 ) ok = 0;
    int kk = 0;
  }

  printf( "%s\n", ok ? "YES" : "NO" );

  return 0;
}

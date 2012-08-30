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

#define N 222

int p[N], n, k;
char str[N];

void mul_perm( int p1[], int p2[], int res[], int n ) {
  int tmp[N];
  REP( i, n ) tmp[i] = p2[p1[i]];
  REP( i, n ) res[i] = tmp[i];
}

void pow_perm( int p[], int res[], int n, int k ) {
  int t[N], s[N];
  REP( i, n ) s[i] = p[i], t[i] = i;
  while( k > 0 ) {
    if ( k & 1 ) mul_perm( t, s, t, n );
    k >>= 1;
    mul_perm( s, s, s, n );
  }
  REP( i, n ) res[i] = t[i];
}

int main() {
  while( scanf( "%d", &n ), n ) {
    REP( i, n ) {  scanf( "%d", &p[i] ); p[i]--; }
    while( scanf( "%d", &k ), k ) {
      CLR( str, 0 );
      getchar();
      gets( str );
      str[n] = 0;
      for( int i = n - 1; i >= 0 && str[i] == 0; i-- ) str[i] = ' ';

      int tmp[N];
      char put[N];
      CLR( put, 0 );
      pow_perm( p, tmp, n, k );
      REP( i, n ) put[tmp[i]] = str[i];
      puts( put );
    }
    puts( "" );
  }
  return 0;
}

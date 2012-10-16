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

#define N 111
#define M 11111

char A[N][M];
int lf[N][M], rt[N][M], n, m;

int main() {
  scanf( "%d%d", &n, &m );

  REP( i, n ) scanf( "%s", A[i] );

  int ok = 1;
  REP( i, n ) {
    int lst = -INF, fst = INF;
    REP( j, m ) if ( A[i][j] == '1' ) {
      fst = min( fst, j );
      lst = max( lst, j );
    }

    if ( lst == -INF ) ok = 0;

    REP( j, m ) {
      if ( A[i][j] == '1' ) lst = j; 
      lf[i][j] = lst;
    }

    for( int j = m - 1; j >= 0; j-- ) {
      if ( A[i][j] == '1' ) fst = j;
      rt[i][j] = fst;
    }
  }

  if ( !ok ) printf( "-1\n" );
  else {
    int ans = INF;

    REP( j, m ) {
      int ll = 0;
      REP( i, n ) {
        ll += min( (j - lf[i][j] + m) % m, (rt[i][j] - j + m) % m );
      }
      ans = min( ll, ans );
    }

    printf( "%d\n", ans );
  }

  return 0;
}

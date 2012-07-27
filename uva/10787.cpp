#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
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

LL find ( int k, int ml, int mu ) {
  LL cnt = 0;
  if ( k == 0 ) return mu - ml + 1;
  for ( int i = 1; i * i <= k; i++ ) {
    if ( k % i == 0 ) {
      if ( i >= ml && i <= mu ) cnt++;
      if ( i * i != k && k / i >= ml && k / i <= mu ) cnt++;
    }
  }
  return cnt;
}

int main() {
  int T;
  scanf( "%d", &T );
  int cas = 1;
  while ( T-- ) {
    int al, au, bl, bu, ml, mu;
    scanf( "%d%d%d%d%d%d", &al, &au, &bl, &bu, &ml, &mu );
    
    LL cnt = 0;
    for ( int k = bl; k <= bu; k++ ) {
      int b = abs( 2 * k );
      cnt += find( b, ml, mu );
    }
    
    cnt *= ( au - al + 1 );

    printf( "Case %d: %lld\n", cas++, cnt );
  }
  return 0;
}

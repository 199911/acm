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

// the last nonzero digit of m * .... * n
// assume m < n

LL getX( LL n, LL p ) {
  LL ret = 0;
  while ( n ) {
    ret += n / p;
    n /= p;
  }
  return ret;
}

LL getY( LL n, LL d ) {
  LL ret = 0;
  for ( LL k = n; k > 0; k /= 5 ) {
    for ( LL l = k; l > 0; l /= 2 ) {
      ret += l / 10 + ( l % 10 >= d );
    }
  }
  return ret;
}

int seq( LL m, LL n ) {
  LL cnt2 = getX( n, 2 ) - ( m ? getX( m - 1, 2) : 0 );
  LL cnt5 = getX( n, 5 ) - ( m ? getX( m - 1, 5) : 0 );
  if ( cnt5 > cnt2 ) return 5;

  LL ans = 1;
  const int d2[] = {6, 2, 4, 8};
  if ( cnt2 > cnt5 ) ans *= d2[(cnt2 - cnt5) % 4];
  
  // find number of 3
  LL cnt3 = getY( n, 3 ) - (m ? getY( m - 1, 3 ) : 0);
  const int d3[] = {1, 3, 9, 7};
  ans *= d3[cnt3 % 4];

  LL cnt7 = getY( n, 7 ) - (m ? getY( m - 1, 7 ) : 0);
  const int d7[] = {1, 7, 9, 3};
  ans *= d7[cnt7 % 4];

  LL cnt9 = getY( n, 9 ) - (m ? getY( m - 1, 9 ) : 0);
  const int d9[] = {1, 9};
  ans *= d9[cnt9 % 2];

  return ans % 10;
}

int main() {

  LL a, b;
  while ( scanf( "%lld%lld", &a, &b ) != EOF ) {
    printf( "%d\n", seq( a, b ) );
  }
  return 0;
}

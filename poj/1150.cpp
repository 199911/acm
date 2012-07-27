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

// compute the last nonzero digit of m * ( m + 1 ) * ( m + 2 ) ... * n

int P( LL m, LL n ) {
  if ( m > n ) return 1;
  LL s = m / 5 + (m % 5 ? 1 : 0), t = n / 5;
  if ( t <= s + 1 ) {
    LL res = 1;
    for ( LL k = m; k <= n; k++ ) {
      LL x = k; 
//      printf( "x = %lld\n", x );
      while ( x % 10 == 0 ) { x /= 10; }
//      while ( res % 5 == 0 && x % 2 == 0 ) { res /= 5; x /= 2; }
//      while ( res % 2 == 0 && x % 5 == 0 ) { res /= 2; x /= 5; }
      res = res * ( x % 1000 );
//      printf("res = %lld\n", res);
    }
    while ( res % 10 == 0 ) res /= 10;
    return res % 10;
  }
  const int A[4] = {6, 2, 4, 8};
  const int D1[5] = {1, 4, 4, 2, 4};
  const int D2[5] = {1, 1, 2, 6, 4};
  LL ret = A[(t - s - 1) % 4] * P(s, t) * D1[m % 5] * D2[n % 5];
  while ( ret % 10 == 0 ) ret /= 10;
  return ret % 10;
}

int main() {
  LL m, n;
  while( scanf( "%lld%lld", &m, &n ) != EOF ) {
    if ( n && m ) printf( "%d\n", P(m - n + 1, m) );
    else printf( "1\n" );
  }
  return 0;
}

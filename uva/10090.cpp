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

#define FOR(i,a,b) for (LL i = (a); i < (b); i++)
#define FOE(i,a,b) for (LL i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<LL,int>
#define PDI pair<double,LL>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

LL egcd( LL a, LL b, LL &s, LL &t ) {
  if ( b == 0 ) { 
    s = 1; t = 0; 
    return a;
  } 
  LL r = egcd(b, a % b, t, s );
  t -= ( a / b ) * s;
  return r;
}

int main() {
  LL n, n1, n2, c1, c2, s, t;

  while ( cin >> n, n ) {
    cin >> c1 >> n1 >> c2 >> n2;

    LL r = egcd ( n1, n2, s, t );
    LL x = n2 / r, y = n1 / r;

    if ( n % r ) {
      puts( "failed" );
    } else {
      s *= n / r;
      t *= n / r;
      if ( c1 * n2 < c2 * n1 ) {
        LL a = t / y + ( t % y < 0 ? -1 : 0 );
        
        s += a * x;
        t -= a * y;
        if ( s >= 0 && t >= 0 ) printf( "%lld %lld\n", s, t );
        else puts( "failed" );
      } else {
        LL a = s / x + ( s % x < 0 ? -1 : 0 );

        s -= a * x;
        t += a * y;

        if ( s >= 0 && t >= 0 ) printf( "%lld %lld\n", s, t );
        else puts( "failed" );
      }
    }
  }
  return 0;
}

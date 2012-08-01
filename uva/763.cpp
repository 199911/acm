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

int main() {
  int a[111], n, first = 1;
  string s, t;

  while ( cin >> s >> t ) {

    reverse( s.begin(), s.end());
    reverse( t.begin(), t.end());

    CLR( a, 0 );

    REP( i, s.length() ) {
      a[i] += s[i] - '0';
    }

    REP( i, t.length() ) {
      a[i] += t[i] - '0';
    }

    n = max( s.length(), t.length() ) ;

    while ( true ) {
      int ok = 0;

      REP( i , n ) {
        if ( a[i] && a[i + 1] ) {
          a[i]--;
          a[i + 1]--;
          a[i + 2]++;
          if ( n == i + 2 ) n++;
          ok = 1;
          break;
        }

        if ( a[i] > 1 ) {
          if ( i == 0 ) {
            a[i] -= 2;
            a[i + 1]++;
          } else if ( i == 1 ) {
            a[i] -= 2;
            a[i - 1]++;
            a[i + 1]++;
          } else {
            a[i] -= 2;
            a[i - 2]++;
            a[i + 1]++;
          }
          if ( i + 1 == n ) n++;
          ok = 1;
          break;
        }
      }
      if ( !ok ) break;
    }

    if ( ! first ) puts( "" );
    for ( int i = n - 1; i >= 0; i-- ) printf( "%d", a[i] );
    puts( "" );
    
    first = 0;
  }
  return 0;
}

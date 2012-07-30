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

int main() {
  int b, d, T;
  cin >> T;

  while ( T-- ) {
    cin >> b >> d;

    int res = b % d, rm = -1, aa = -1, at = -1;

    for ( int i = 1; i <= 1000; i++ ) {
      if ( res % d == 0 && rm == -1 ) rm = i;
      if ( res % d == d - 1 && at == -1 ) at = i;
      if ( res % d == 1 && aa == -1 ) aa = i;
      res *= b; res %= d; 
    }

    if ( rm != -1 ) {
      printf( "Rightmost %d\n", rm );
    } 

    if ( aa != -1 ) {
      printf( "Add all %d\n", aa );
    }

    if ( at != -1 ) {
      printf( "Alternate %d change sign\n", at );
    }

    if ( rm == -1 && aa == -1 && at == -1 ) puts( "condition not found." );

    if ( T ) puts( "" );
    
  }
  return 0;
}

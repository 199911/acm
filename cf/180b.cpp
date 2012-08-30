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

int gcd( int a, int b ) { return b ? gcd( b, a % b ) : a; }

int type[111];

int main() {
  CLR( type, 0 );
  int b = 0, div;
  cin >> b >> div;
  for( int d = 2; d <= b; d++ ) 
    if ( b % d == 0 ) type[d] = 2;
  for( int d = 2; d <= 100; d++ ) 
    for( int i = 2; i * i <= d; i++ ) 
      if ( d % i == 0 ) 
        if ( type[i] == 2 && type[d / i] == 2 ) { 
          type[d] = 2;
          break;
        }
  for( int d = 2; d < b; d++ )
    if ( (b - 1) % d == 0) {
      if ( type[d] == 0 ) type[d] = 3;
    }
  for( int d = 2; d <= b + 1; d++ ) {
    if ( (b + 1) % d == 0 && type[d] == 0 ) type[d] = 11;
  }
  for( int d = 2; d <= 100; d++ ) {
    if ( type[d] == 0 ) {
      for( int i = 2; i < d; i++ ) {
        if ( d % i == 0 && d % (i * i)) {
          if ( type[i] == 2 && type[d / i] == 3 ) type[d] = 6;
          if ( type[i] == 2 && type[d / i] == 11 ) type[d] = 22;
          if ( type[i] == 3 && type[d / i] == 11 ) type[d] = 33;
          if ( type[i] == 2 && type[d / i] == 33 ) type[d] = 66;
          if ( type[i] == 3 && type[d / i] == 22 ) type[d] = 66;
          if ( type[i] == 11 && type[d / i] == 66 ) type[d] = 66;
          if ( type[d] ) break;
        }
      }
    }
  }

  for( int i = 2; i <= 100; i++ ) 
    if ( !type[i] ) type[i] = 7;
    else if ( type[i] == 22 || type[i] == 33 || type[i] == 66 ) type[i] = 6;
  printf( "%d-type\n", type[div] );
  if ( type[div] == 2 ) {
    int cnt = 0, r = gcd( div, b );
    while ( r > 1 ) {
      div /= r;
      cnt++;
      r = gcd( div, b );
    }
    printf( "%d\n", cnt );
  }
  return 0;
}

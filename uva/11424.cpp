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

#define N 200004

void genphi( LL ph[], int n ) {
  for ( int i = 0; i < n; i++ ) ph[i] = i;
  ph[1] = 0;
  for ( int i = 2; i < n; i++ ) 
    if ( ph[i] == i ) {
      ph[i]--;
      for ( int j = i + i; j < n; j += i ) ph[j] = ph[j] / i * ( i - 1 );
    }
}

LL as( LL a, LL b ) {
  if ( b < a ) return 0;
  return ( a + b ) * ( b - a + 1) / 2;
}

LL ph[N], ps[N], ss[N];

int main() {
  genphi( ph, N );
  ps[0] = 0;
  for ( int i = 1; i < N; i++ ) ps[i] = ph[i] + ps[i - 1];
  CLR( ss, 0 );

  LL n;

  while ( scanf( "%lld", &n ), n ) {
    LL s = 0;
    for ( LL i = 1; SQR(i) <= n; i++ ) {
      if ( i !=  n / i ) {
        LL en = n / i;
        LL st = n / ( i + 1 ) + 1;
        s += as(st, en) * ps[i];
        s += i * ps[n / i];
      } else {
        s += i * ps[n / i];
      }
    }
    printf( "%lld\n", s );
  }

  
  return 0;
}

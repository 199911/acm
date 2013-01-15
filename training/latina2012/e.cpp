#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

double eps = 1e-4;
double p[2][9], q[2][9], a, w, d;
int k;

double f1( double x ) {
  double no = 0.0, de = 0.0;
  for( int i = k; i >= 0; i-- ) {
    no *= x; de *= x;
    no += p[0][i]; de += q[0][i];
  }
  return no / de;
}

double f2( double x ) {
  double no = 0.0, de = 0.0;
  for( int i = k; i >= 0; i-- ) {
    no *= x; de *= x;
    no += p[1][i]; de += q[1][i];
  }
  return no / de;
}

double height( double x, double d ) {
  double y1 = f1( x ), y2 = f2( x );
  if ( y2 > d ) return y1 - y2;
  else if ( y1 < d ) return 0.0;
  return y1 - d;
}

double find( double d ) {
  double ar = 0.0, lst = height( 0.0, -d );
  for( double x = eps; x < w + 1e-9; x += eps ) {
    double cur = height( x, -d );
    double mid = height( x - 0.5 * eps, -d );
//    ar += ( cur + 4 * mid + lst ) / 6.0 * eps;
    ar += ( cur + lst ) / 2.0 * eps;
    lst = cur;
  }
  return ar;
}

int main() {
  while( scanf( "%lf%lf%lf%d", &w, &d, &a, &k ) != EOF ) {
    for( int i = 0; i <= k; i++ ) scanf( "%lf", &p[0][i] );
    for( int i = 0; i <= k; i++ ) scanf( "%lf", &q[0][i] );
    for( int i = 0; i <= k; i++ ) scanf( "%lf", &p[1][i] );
    for( int i = 0; i <= k; i++ ) scanf( "%lf", &q[1][i] );

    double hi = d, lo = 0.0;

    while( hi > lo + 2e-6 ) {
      double mid = ( hi + lo ) / 2.0;
      double ar = find( mid );
      if ( ar < a ) lo = mid;
      else hi = mid;
    }

    printf( "%.5f\n", hi );
  }
  return 0;
}

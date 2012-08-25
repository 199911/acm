#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

#define sqr(a) ((a)*(a))

int main() {
  int n, cas = 1;
  while ( scanf( "%d", &n ), n ) {
    double x[111], y[111];
    for( int i = 0; i < n; i++ ) scanf( "%lf%lf", &x[i], &y[i] );

    double ans = 1e10;
    for( int i = 0; i < n; i++ ) {
      for( int j = i + 1; j < n; j++ ) {
        double mag = sqrt( sqr( x[i] - x[j]) + sqr(y[i] - y[j]) );
        double u = x[j] - x[i], v = y[j] - y[i];
        double up = 0.0, lo = 0.0;
        for( int k = 0; k < n; k++ ) {
          double s = x[k] - x[i], t = y[k] - y[i];
          double prod = u * t - v * s;
          double hi = prod / mag;
          up = max( up, hi );
          lo = min( lo, hi );
        }
        ans = min( ans, up - lo );
      }
    }
    printf( "Case %d: %.2f\n", cas++, ans + 0.005);
  }

  return 0;
}

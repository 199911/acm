#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

double ans = 1e10, a[111111], PI = atan( 1.0 ) * 4.0;
int n;

int main() {
  scanf( "%d", &n );
  for( int i = 0; i < n; i++ ) {
    double x, y, ag;
    scanf( "%lf%lf", &x, &y );
    ag = atan2( y, x );
    a[i] = ag;
  }
  sort( a, a + n );
  a[n++] = a[0] + 2.0 * PI;
  for( int i = 0; i < n - 1; i++ ) {
    ans = min( ans, 2 * PI - ( a[i + 1] - a[i] ) );
  }

  printf( "%.9f\n", ans * 180.0 / PI );

  return 0;
}

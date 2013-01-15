#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int k, n, m, a[111], t;

int main() {
  scanf( "%d%d%d", &n, &m, &k );
  for( int i = 0; i < n; i++ )
    scanf( "%d", &a[i] );
  sort( a, a + n );

  int ans = 0;
  for( int i = n - 1; i >= 0; i-- ) {
    if ( m <= k ) break;
    ans++;
    k--;
    k += a[i];
  }

  if ( m > k ) puts( "-1" );
  else printf( "%d\n", ans );

  return 0;
}

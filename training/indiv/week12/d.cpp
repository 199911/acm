#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 111111
#define LL long long

LL stk[N], a[N], ans;
int n, sn, l[N], r[N];

int main() {
  while( scanf( "%d", &n ), n ) {
    for( int i = 0; i < n; i++ ) scanf( "%lld", &a[i] );
    sn = 0;
    for( int i = 0; i < n; i++ ) {
      while ( sn && a[stk[sn - 1]] >= a[i] ) sn--;
      if ( sn == 0 ) {
        l[i] = 0;
      } else {
        l[i] = stk[sn - 1] + 1;
      }
      stk[sn++] = i;
    }

    sn = 0;

    for( int i = n - 1; i >= 0; i-- ) {
      while ( sn && a[stk[sn - 1]] >= a[i] ) sn--;
      LL cur;
      if ( sn == 0 ) {
        r[i] = n - 1;
      } else {
        r[i] = stk[sn - 1] - 1;
      }
      stk[sn++] = i;
      if ( ans < cur ) ans = cur;
    }

    LL ans = 0;
    for( int i = 0; i < n; i++ ) 
      ans = max( ans, a[i] * ( r[i] - l[i] + 1 ) );




    printf( "%lld\n", ans );
  }
  return 0;
}

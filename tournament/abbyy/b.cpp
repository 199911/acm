#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 333333

int a[N], p[N], n, t, x, y, bit[N], q;

void update( int t, int x ) {
//  printf( "update %d %d\n", t, x );
  for( int i = t; i < N; i += i & -i ) 
    bit[i] += x;
}

int query( int p ) {
  if( p <= 0 ) return 0;
  int ans = 0;
  for( int i = p; i > 0; i -= i & -i ) 
    ans += bit[i];
  return ans;
}

int query( int a, int b )  {
  return query( b ) - query( a - 1 );
}

int main() {
  memset( bit, 0, sizeof( bit ) );
  scanf( "%d", &n );
  for( int i = 1; i <= n; i++ ) {
    scanf( "%d", &a[i] );
    p[a[i]] = i;
  }
  for( int i = 1; i <= n - 1; i++ ) update( i, p[i] > p[i + 1] );
  scanf( "%d", &q );
  for( int i = 0; i < q; i++ ) {
    scanf( "%d%d%d", &t, &x, &y );
    if ( t == 1 ) {
      printf( "%d\n", query( x, y - 1 ) + 1 );
    } else {
      x = a[x]; y = a[y];
      swap( p[x], p[y] );
      a[p[x]] = x;
      a[p[y]] = y;
      if ( x > 1 ) 
        update( x - 1, -query( x - 1, x - 1 ) );
      update( x, -query( x, x ) );
      if ( x != y - 1 )
        update( y - 1, -query( y - 1, y - 1 ) );
      if ( y < n )
        update( y, -query( y, y ) );

      if ( x > 1 ) 
        update( x - 1, p[x - 1] > p[x] );
      update( x, p[x] > p[x + 1] );
      if ( y - 1 != x )   
        update( y - 1, p[y - 1] > p[y] );
     if ( y < n ) 
       update( y, p[y] > p[y + 1] );
    }
  }
  return 0;
}

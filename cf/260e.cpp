#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int ct[3][3], a[10], fl[10], n, x[111111], y[111111];

void dfs( int k ) {
  for( int i = 0; i < 9; i++ ) {
    if ( fl[i] == 0 ) {
    }
  }
}

int main() {
  scanf( "%d", &n );
  for( int i = 0; i < n; i++ ) scanf( "%d%d", &x[i], &y[i] );
  for( int i = 0; i < 9; i++ ) scanf( "%d", &a[i] );
  memset( fl, 0, sizeof( fl ) );
  
  dfs( 0 );


  return 0;
}

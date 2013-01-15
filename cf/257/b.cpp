#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int y[2], x[2], a[111111], s, t, as, at, n; 

int main() {
  t = 0; s = 0;
  scanf( "%d%d", &x[0], &x[1] );
  y[0] = x[0]; 
  y[1] = x[1]; 
  n = x[0] + x[1]; 
  for( int i = 0; i < n; i++ ) {
    if ( i == 0 ) { y[0]--; a[i] = 0; }
    else if ( i & 1 ) { 
      int k = a[i - 1] ^ 1;
      if ( y[k] ) {
      } else {
        k = k ^ 1;
      }
      y[k]--;
      a[i] = k;
    } else {
      int k = a[i - 1];
      if ( y[k] ) {
      } else {
        k = k ^ 1;
      }
      y[k]--;
      a[i] = k;
    }
  }
  as = at = 0;
  for( int i = 0; i < n - 1; i++ ) {
    if ( a[i] == a[i + 1] ) as++;
    else at++;
  }
  y[0] = x[0]; 
  y[1] = x[1]; 
  for( int i = 0; i < n; i++ ) {
    if ( i == 0 ) { y[1]--; a[i] = 1; }
    else if ( i & 1 ) { 
      int k = a[i - 1] ^ 1;
      if ( y[k] ) {
      } else {
        k = k ^ 1;
      }
      y[k]--;
      a[i] = k;
    } else {
      int k = a[i - 1];
      if ( y[k] ) {
      } else {
        k = k ^ 1;
      }
      y[k]--;
      a[i] = k;
    }
  }
  s = t = 0;
  for( int i = 0; i < n - 1; i++ ) {
    if ( a[i] == a[i + 1] ) s++;
    else t++;
  }

  if ( s > as ) {
    printf( "%d %d\n", s, t );
  } else {
    printf( "%d %d\n", as, at );
  }

  return 0;
}

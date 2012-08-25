#include <cstdio>
#include <cstring>

int main() {
  int p[44444], pn = 0;
  bool ip[44444];
  memset( ip, 1, sizeof(ip) );

  for( int i = 2; i < 44444; i++ ) 
    if ( ip[i] ) {
      p[pn++] = i;
      for( int j = i + i; j < 44444; j += i ) ip[j] = 0;
    }

  int n;
  while ( scanf( "%d", &n ), n ) {
    int res = 0;
    for( int i = 1; i <= n; i++ ) {
      res = res + p[n-i];
      res %= i;
    }
    printf( "%d\n", res + 1 );
  }

  return 0;
}

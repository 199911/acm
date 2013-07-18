#include <cstdio>
#include <cstring>
#include <algorithm>

int main() {
  int a, b;
  scanf( "%d%d", &a, &b );
  printf( "%d\n", a + b - 1 );
  for( int i = 1; i <= b; i++ ) printf( "1 %d\n", i );
  for( int i = 2; i <= a; i++ ) printf( "%d 1\n", i );
  return 0;
}

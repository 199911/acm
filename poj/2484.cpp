#include <cstdio>

int main() {
  int n;
  while( scanf( "%d", &n ), n ) {
    if ( n <= 2 ) puts( "Alice" );
    else puts( "Bob" );
  }

  return 0;
}


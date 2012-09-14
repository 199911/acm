#include <cstdio>

#define DIV(a, b) ((a)/(b)+!!((a)%(b)))

int main() {
  long long n;

  while( scanf( "%lld", &n ) != EOF ) {
    while( n > 18 ) {
      n = DIV( n, 18 );
    }
    if ( n <= 9 ) puts( "Stan wins." );
    else puts( "Ollie wins." );
  }
  return 0;
}

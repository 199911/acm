#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
  char s[111111];
  int n, dl = 0;

  scanf( "%s", s );

  n = strlen( s );
  for( int i = 0; i < n; i++ ) {
    if ( s[i] == '0' && dl == 0 ) {
      dl = 1;
    } else if ( i == n - 1 && dl == 0 ) {
      dl = 1;
    } else {
      putchar( s[i] );
    }
  }
  puts( "" );

  return 0;
}

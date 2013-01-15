#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int main() {
  string st;
  int a, b, n, ok = 1;
  scanf( "%d%d%d", &a, &b, &n ); 

  st = static_cast<ostringstream*>( &(ostringstream() << a ) )->str();
  a %= b;

  for( int i = 0; i < n; i++ ) {
    int kk = 0;
    for( int j = 0; j < 10; j++ ) {
      if ( ( a * 10 + j ) % b == 0 ) {
        a = 0;
        kk = 1;
        st.append( 1, '0' + j );
        break;
      }
    }
    if( !kk ) { 
      ok = 0;
      break;
    }
  }

  if ( ok ) printf( "%s\n", st.c_str() );
  else puts( "-1" );

  return 0;
}

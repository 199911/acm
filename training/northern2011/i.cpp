#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int main() {
  char str[1111];
  scanf( "%s", str );
  int l = strlen(str);
  char x = str[l - 1];
  str[l - 1] = '\0';
  int k = atoi( str );

  if ( k <= 2 ) {
    if ( x == 'A' || x == 'D' ) puts( "window" );
    else puts ( "aisle" );
  } else if ( k <= 20 ) {
    if ( x == 'A' || x == 'F' ) puts( "window" );
    else puts( "aisle" );
  } else {
    if ( x == 'A' || x == 'K' ) puts ( "window" );
    else if ( x == 'C' || x == 'D' || x == 'G' || x == 'H' ) puts( "aisle" );
    else puts( "neither" );
  }

  return 0;
}

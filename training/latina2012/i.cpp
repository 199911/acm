#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 111111

void update( int b[], int k, int a )  {
  for( int i = k; i < N; i += i & -i ) 
    b[i] += a;
}

int query( int b[], int x ) {
  int ans = 0;
  for( int i = x; i > 0; i -= i & -i )
    ans += b[i];
  return ans;
}

int query( int b[], int x, int y ) {
  return query( b, y ) - ( x == 1 ? 0 : query( b, x - 1 ) );
}

int a[N], ng[N], zr[N], n, q;

int main() {
  while( scanf( "%d%d", &n, &q ) != EOF ) {
    CLR( ng, 0 );
    CLR( zr, 0 );
    REP( i, n ) {
      scanf( "%d", &a[i] );
      if ( a[i] == 0 ) update( zr, i + 1, 1 );
      else if ( a[i] < 0 ) update( ng, i + 1, 1 );
    }
    
    REP( i, q ) {
      char s[2];
      int x, y;
      scanf( "%s%d%d", s, &x, &y );
      if ( s[0] == 'C' ) {
        if ( a[x - 1] == 0 ) update( zr, x, -1 );
        if ( a[x - 1] < 0 ) update( ng, x, -1 );
        if ( y == 0 ) update( zr, x, 1 );
        if ( y < 0 ) update( ng, x, 1 );
        a[x - 1] = y;
      } else {
        if ( query( zr, x, y ) > 0 ) printf( "0" );
        else {
          int h = query( ng, x, y );
          if ( h & 1 ) printf( "-" );
          else printf( "+" );
        }
      }
    }
    puts( "" );
    
  }
  return 0;
}

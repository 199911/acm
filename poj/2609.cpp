#include <cstdio>
#include <cstring>
using namespace std;

int dp[202][10001];
int pf[202][10001];
int car[202];

void print( int n, int a ) {
  if ( n == 0 ) return;
  if ( pf[n][a] == 1 ) {
    print( n - 1, a - car[n - 1] );
    puts( "port" );
  } else {
    print( n - 1, a );
    puts( "starboard" );
  }

}

int main(){
  int l = 0, n = 0;
  scanf( "%d", &l );
  l *= 100;

  memset( dp, -1, sizeof(dp) );

  int fl = 0, k = 1, ans;

  dp[0][0] = 0;

  while( scanf( "%d", &k ), k ) {
    int ok = 0; 
    car[n] = k;
    for( int i = 0; i <= l; i++ ) {
      if ( dp[n][i] >= 0 ) {
        if ( i + k <= l ) {
          dp[n + 1][i + k] = dp[n][i];
          pf[n + 1][i + k] = 1;
          ok = 1;
        } 
        if ( dp[n][i] + k <= l ) {
          dp[n + 1][i] = dp[n][i] + k;
          pf[n + 1][i] = 0;
          ok = 1;
        }
      }
    }
    if ( !ok ) break;
    n++;
    ans = n;
  }

  printf( "%d\n", ans );

  for( int i = 0; i <= l; i++ ) {
    if ( dp[ans][i] != -1 ) {
      print( ans, i );
      break;
    }
  }

  return 0;
}

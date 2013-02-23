#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define LL long long

LL f( LL a ) {
  if ( !a ) return 0;
  if ( a & 1 ) return f( a >> 1 ) + 1;
  else return f( a >> 1 ); 
}


int main() {
  LL a[11111], ans;
  int n, cnt[111];
  scanf( "%d", &n );
  memset( cnt, 0, sizeof(cnt) );
  ans = 0;
  for( int i = 0; i < n; i++ ) {
    scanf( "%lld", &a[i] );
    cnt[f( a[i] )]++;
  }
  for( int i = 0; i < 111; i++ )
    ans += (LL)cnt[i] * ( cnt[i] - 1 );
  ans >>= 1;
  printf( "%lld\n", ans );
  return 0;
}

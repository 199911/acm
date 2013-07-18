#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <map>
using namespace std;

#define LL long long 

#define N 333333

map<LL, int> mp;
LL ps[N], a[N];
int n, first, last;
LL sum = LLONG_MIN;

int main() {
  scanf( "%d", &n );
  ps[0] = 0;
  mp.clear();
  for( int i = 1; i <= n; i++ ) { 
    scanf( "%lld", &a[i] );
    ps[i] = ps[i - 1] + max( a[i], 0LL );
    if( mp.find( a[i] ) == mp.end() ) {
      mp[a[i]] = i;
    } else {
      int s = mp[a[i]], t = i;
      LL ts = a[i] + ps[t - 1] - ps[s] + a[s];
      if ( ts > sum ) {
        sum = ts;
        first = s;
        last = t;
      }
    }
  }

  int cnt = 0;
  for( int i = 1; i <= n; i++ ) {
    if( i < first || i > last || i > first && i < last && a[i] < 0 ) cnt++;
  }
  bool bg = 1;
  printf( "%lld %d\n", sum, cnt );
  for( int i = 1; i <= n; i++ ) {
    if( i < first || i > last || i > first && i < last && a[i] < 0 ) {
      if ( !bg ) printf( " " );
      bg = 0;
      printf( "%d", i );
    }
  }
  puts( "" );

  return 0;
}

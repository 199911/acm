#include <cstdio>

int main() {
  long long n, m, cur, ans;

  scanf( "%lld%lld", &n, &m );

  ans = 1, cur = 3;
  while( n ) {
    if ( n & 1 ) { 
      ans *= cur; ans %= m; 
    }
    cur *= cur; cur %= m;
    n >>= 1;
  }

  ans += m - 1;
  ans %= m;
  printf( "%lld\n", ans );

  return 0;
}

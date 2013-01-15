#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define FOR(i,a,b) for( int i = (a); i < (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define LL long long

#define N 16
#define MOD 1000000007LL

LL count( LL k ) {
  LL ret = 0;
  while( k ) {
    if ( k % 10 == 4 || k % 10 == 7 ) ret++;
    k /= 10;
  }
  return ret;
}

void doit( LL n, LL cnt[] ) {
  if ( n < 10 ) {
    REP( i, N ) cnt[i] = 0;
    REP( i, n + 1 ) cnt[i == 4 || i == 7] += 1;
    return;
  }
  LL tmp[N];
  REP( i, N ) cnt[i] = 0;
  doit( n / 10 - 1, tmp );
  REP( i, N ) cnt[i] += tmp[i] * 8;
  REP( i, N - 1 ) cnt[i + 1] += tmp[i] * 2;
  LL st = n / 10 * 10;
  for( LL i = st; i <= n; i++ ) {
    cnt[count(i)]++;
  }
}

LL n, cnt[N];

LL dfs( int k, int lft ) {
  if ( k == 0 ) return 1;
  LL ans = 0;
  for( int i = 0; i <= lft; i++ ) {
    if ( cnt[i] ) {
      cnt[i]--;
      ans = ( ans + ( cnt[i] + 1 ) * dfs( k - 1,  lft - i ) ) % MOD;
      cnt[i]++;
    }
  }
  return ans;
}

int main() {
  scanf( "%lld", &n );
  doit( n, cnt );
  cnt[0]--;
  LL ans = 0;
  FOR( i, 1, N ) {
    if ( cnt[i] ) {
      ans += dfs( 6, i - 1 ) * cnt[i];
      ans %= MOD;
    }
  }

  printf( "%lld\n", ans );

  return 0;
}


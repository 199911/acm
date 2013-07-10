#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define LL long long
#define ULL unsigned long long

int pr[111] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 };

ULL ans, K;

ULL gcd( ULL a, ULL b ) { return b ? gcd( b, a % b ) : a; }

bool check( ULL a, ULL b, ULL c, ULL &d) {
  ULL g = gcd( a, c );
  a /= g; c /= g;
  g = gcd( b, c );
  b /= g; c /= g;
  if ( c > 1 || a > ULLONG_MAX / b ) return false;
  d = a * b;
  return true;
}

void dfs( int d, int tot, int mx, ULL cnt, ULL k ) {
  if ( K % cnt ) return;
  for( int i = 1; i <= mx; i++ ) {
    ULL tmp;
    if ( k > ULLONG_MAX / pr[d] || !check( cnt, tot + i, i, tmp ) ) break;
    k *= pr[d];
    cnt = tmp;
    if ( cnt > K ) break;
    else if ( cnt == K ) {
      if ( ans == 0 || ans > k ) ans = k;
    } else {
      dfs( d + 1, tot + i, i, cnt, k );
    }
  }
}

int main() {
  while( scanf( "%llu", &K ) != EOF ) {
    ans = 0;
    dfs( 0, 0, 63, 1, 1 );
    printf( "%llu %llu\n", K, ans );
  }
  return 0;
}

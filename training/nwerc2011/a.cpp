#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define FOE(i,a,b) for(int i = a; i <= b; i++)
#define REP(i,n) FOR(i,0,n)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define MAX 1000000000000001LL

struct T {
  LL a, b;
  T() {}
  T( LL a, LL b ): a(a), b(b) {}
  
  bool operator<(const T &t ) const {
    return a < t.a || a == t.a && b < t.b;
  }
};
const double MAXLOG = log( (double) MAX );

LL choose( LL n, LL r ) {
  double t = 0.0;
  for( LL i = 0; i < r; i++ ) t += log( (double)n - i );
  for( LL i = 1; i <= r; i++ ) t -= log( (double) i );
  if ( t > MAXLOG ) return MAX;
  LL ans = 1;
  for( LL i = 1; i <= r; i++ ) {
    ans *= n - r + i;
    ans /= i;
  }
  return ans;
}

bool search( LL x, LL r, LL &ans ) {
  if ( choose( r << 1, r ) > x ) return false;
  else if ( choose( r << 1, r ) == x ) {
    ans = r << 1;
    return true;
  }
  LL hi = MAX, lo = r << 1;
  while( hi > lo + 1 ) {
    LL mid = (hi + lo) >> 1, y = choose( mid, r );
//    printf( "(%lld,%lld) = %lld\n", mid, r, y );
    if ( y == x ) {
      ans = mid;
      return true;
    } else if ( y > x ) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  return false;
}

int main() {
  int cas;
  LL m;
  vector<T> V;
  scanf( "%d", &cas );
  while( cas-- ) {
    scanf( "%lld", &m );
    V.clear();
    LL n;
    for( LL i = 1; i <= 100; i++ ) {
      if ( search( m, i, n ) ) {
        V.push_back( T( n, i ) );
        if ( i << 1 != n ) V.push_back( T( n, n - i) );
      }
    }
    sort( V.begin(), V.end() );
    printf( "%d\n", V.size() );
    for( vector<T>::iterator it = V.begin(); it != V.end(); it++ ) {
      if ( it != V.begin() ) printf( " " );
      printf( "(%lld,%lld)", it->a, it->b );
    }
    puts( "" );
  }
  return 0;
}


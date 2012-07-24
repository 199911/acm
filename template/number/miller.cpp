#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

LL exp( LL a, LL b, LL m ) {
  LL res = 1;
  for( LL k = 1, t = a; k <= b; k <<= 1, t *=  t, t %= m ) 
    if ( k & b ) { 
      res *= t; res %= m;
    }
  return res;
}

bool prime( LL n ) {
  srand(time(NULL));

  LL k = 0;
  for( LL x = 1; x <= n; x *= 2 ) k++;

  REP(iter, k) {
    LL a = rand() % (n - 1) + 1;
    LL r = n - 1;
    if ( exp( a, r, n ) != 1 ) return false;
    while ( true ) {
      LL t = exp( a, r, n );
      if ( t == n - 1 ) break;
      else if ( t != 1 ) return false;
      if ( r % 2 == 0 ) r /= 2;
      else break;
    }
  }
  return true;
}

int main() {
  LL n;
  while ( scanf( "%lld", &n ) != EOF ) {
    printf( "%s\n", prime(n) ? "YES" : "NO" );  
  }
  return 0;
}

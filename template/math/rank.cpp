#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
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
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
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

#define MOD 1000000007

LL exp( LL a, LL b, LL m ) {
  LL ret = 1;
  while( b ) {
    if ( b & 1 ) ret *= a %= m;
    a *= a %= m;
    b >>= 1;
  }
  return ret;
}

LL inv( LL a, LL p ) {
  return exp( a, p - 2, p );
}

int rank( LL **A, int m, int n, LL p ) {
  int rnk = 0;
  for( int i = 0, row = 0; i < n && row < m; i++ ) {
    if ( A[row][i] = 0 ) 
      for( int j = row + 1; j < m; j++ ) 
        if ( A[j][i] ) {
          for( int k = i; i < n; i++ ) swap( A[row][k], A[j][k] );
          break;
        }
    if ( A[row][i] ) {
      rnk++;
      LL iv = inv( A[row][i], p );
      for( int j = row + 1; j < m; j++ ) {
        LL mul = iv * A[j][i] % p;
        if ( mul ) 
          for( int k = i; k < n; k++ ) 
            A[j][k] -= A[row][k] * mul % p;
      }
      row++;
    }
  }
  return rnk;
}

LL** aloc( int m, int n ) {
  LL **ret = ( LL ** ) malloc( m * sizeof( LL ** ) );
  for( int i = 0; i < m; i++ ) 
    ret[i] = ( LL * ) calloc( n, sizeof( LL ) ); 
  return ret;
}

int main() {
  return 0;
}

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

#define N 300

#define NOR(a,b) ((a)=((a)%(b)+(b))%(b))

LL deter( LL A[N][N], int n, LL m ) {
  LL sgn = 1, ret = 1;
  for( int i = 0; i < n; i++ ) {
    if ( A[i][i] == 0 ) {
      for( int j = i + 1; j < n; j++ ) 
        if ( A[j][i] != 0 ) {
          for( int k = i; k < n; k++ ) 
            swap( A[i][k], A[j][k] );
          sgn *= -1;
          break;
        }
      if ( A[i][i] == 0 ) return 0;
    }

    for( int j = i + 1; j < n; j++ ) {
      int s = i, t = j;
      while( A[s][i] != 0 && A[t][i] != 0 ) {
        LL q = A[s][i] / A[t][i];
        for( int k = i; k < n; k++ ) { 
          A[s][k] -= A[t][k]  * q;
          NOR( A[s][k], m );
        }
        swap( s, t );
      }
      if ( A[t][i] == 0 ) swap( s, t );
      if ( s == i ) {
        for( int k = i; k < n; k++ ) 
          swap( A[i][k], A[j][k] );
        sgn *= -1;
      }
    }

    ret *= A[i][i];
    NOR( ret, m );
  }

  ret *= sgn;
  NOR( ret, m );
  return ret;
}

int n;
LL A[N][N], m;

int main() {
  while( scanf( "%d%lld", &n, &m ) != EOF ) {
    for( int i = 0; i < n; i++ ) 
      for( int j = 0; j < n; j++ ) 
        scanf( "%lld", &A[i][j] );

    for( int i = 0; i < n; i++ ) 
      for( int j = 0; j < n; j++ )
        NOR( A[i][j], m );

    printf( "%lld\n", deter( A, n, m ) );
  }
  return 0;
}

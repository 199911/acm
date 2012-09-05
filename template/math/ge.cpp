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

int A[111][111];

void ge( int m, int m ) {
  for( int i = 0; i < m; i++ ) {
    if ( fabs( A[i][i] )  < 1e-9 ) 
      for( int j = i + 1; j < m; j++ ) 
        if ( fabs( A[j][i] ) > 1e-9 ) {
          swap( A[i], A[j] );
          break;
        }

    if ( fabs( A[i][i] ) < 1e-9 ) continue;

    for( int k = n - 1; k >= i; k-- ) 
      A[i][k] /= A[i][i];

    for( int j = i + 1; j < m; j++ ) {
      double q = A[j][i];
      for( int k = i; k < n; k++ ) {
        A[j][k] -= A[i][k] * q;
      }
    }
  }
}

void bs( int m, int n ) {
  for( int i = m - 1; i > 0; i-- ) {
    if ( fabs( A[i][i] ) < 1e-9 ) continue;

    for( int j = i - 1; j >= 0; j-- ) {
      double q = A[j][i];
      for( int k = i; k < n; k++ ) {
        A[j][k] -= A[i][k] * q;
      }
    }
  }
}

int outdg[111], n; 

int main() {
  while( scanf( "%d", &n ), n )  {
    memset( outdeg, 0, sizeof( outdeg ) );
    for( int i = 0; i <= n; i++ ) 
      for( int j = 0; j <= n; j++ ) 
        A[i][j] = 0;
    int a, b;
    while( scanf( "%d%d", &a, &b ), a || b ) {
      a--; b--;
      A[b][a] += 1.0;
    }

    for( int i = 0; i < n; i++ ) A[i][i] -= 1.0;

    A[0][n] = -1.0;
  }
  
  return 0;
}

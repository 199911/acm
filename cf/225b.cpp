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
#include <bitset>
#include <map>
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

int main() {
  LL A[111];
  int n, k, s;
  scanf( "%d%d", &s, &k );

  for( int i = 0, cur = 1; cur <= s; i++ ) {
    if ( i < k ) {
      A[i] = 1 << i;
      cur = A[i];
    } else {
      cur = 0;
      for( int j = i - k; j < i; j++ ) cur += A[j];
      A[i] = cur;
    }
    n = i + 1;
  }

  int b[111], m = 0;

  for( int i = n - 1, f = 1; s > 0 && i >= 0; i--, f = 0 ) {
    if ( A[i] <= s ) {
      b[m++] = A[i];
      s -= A[i];
    }
  }

  if( m == 1 ) b[m++] = 0;
  sort( b, b + m );

  printf( "%d\n", m );
  REP( i, m ) printf( "%d%s", b[i], i == m - 1 ? "\n" : " " );


  return 0;
}

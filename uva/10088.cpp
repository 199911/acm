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

#define N 1111

LL area( LL x[], LL y[], int n ) {
  LL ret = 0;

  x[n] = x[0]; y[n] = y[0];
  REP( i, n ) {
    ret += x[i] * y[i + 1] - x[i + 1] * y[i];
  }
  if ( ret < 0 ) ret = -ret;
  ret >>= 1;

  return ret;
}

LL gcd( LL a, LL b ) {
  return b ? gcd( b, a % b ) : a;
}

LL pick( LL x[], LL y[], int n ) {
  LL A = area(x, y, n), b = 0, ret = 0;

  REP( i, n ) {
    b += gcd( abs(x[i] - x[(i + 1) % n]), abs(y[i] - y[(i + 1) % n]));
  }

  return A + 1 - b / 2;
}

int main() {
  LL x[N], y[N];
  int n;

  while ( cin >> n, n ) {
    REP( i, n ) 
      cin >> x[i] >> y[i];
    printf( "%lld\n", pick(x, y, n) );
  }
  
  return 0;
}

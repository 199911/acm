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

// compute the last nonzero digit for n factorial
int L( LL n ) {
  int d[10] = { 1, 1, 2, 6, 4};
  int q[4] = {2, 4, 8, 6};
  if ( n < 10 ) return d[n];  
  return q[n % 4] * L(n / 5) * d[n % 5] % 10;
}

int main() {
  LL m, n;
  while( scanf( "%lld%lld", &m, &n ) != EOF ) {
    printf( "%d\n", P(m - n + 1, m) );
  }
  return 0;
}

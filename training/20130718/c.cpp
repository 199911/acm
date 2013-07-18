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

int n;
LL a[22222], S;

int main() {
  scanf( "%d%lld", &n, &S );
  REP( i, n ) scanf( "%lld", &a[i] );
  sort( a, a + n );
  LL ans = 0;

  for( int s = 0, t = n - 1; s < t; s++ ) {
    while( a[t] + a[s] > S && t > s + 1 ) t--;
    if ( a[t] + a[s] <= S ) ans += t - s;
  }
  printf( "%lld\n", ans );
  return 0;
}

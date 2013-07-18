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

#define N 1111111

int ip[N], p[N], pn, a, d, n;

int main() {
  FOR( i, 2, N ) ip[i] = 1;
  pn = 0;
  for( int i = 2; i < N; i++ ) {
    if ( ip[i] ) {
      p[pn++] = i;
      for( int j = i + i; j < N; j += i ) 
        ip[j] = 0;
    }
  }

  while( scanf( "%d%d%d", &a, &d, &n ), a || d || n )  {
    REP( i, pn ) {
      if ( p[i] >= a && ( p[i] - a ) % d == 0 ) {
        n--;
        if ( n == 0 ) {
          printf( "%d\n", p[i] );
          break;
        }
      }
    }
  }
  return 0;
}

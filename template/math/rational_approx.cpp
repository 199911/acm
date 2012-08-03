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

LL MAX;

// find the smallest term in the  Farey series that is >= a/b
// assume a / b < 1
void rational_approx( LL a, LL b, LL &lm, LL &ln, LL &rm, LL &rn ) {
  if ( a == 0 ) {
    lm = rm = 0; ln = rn = 1;
    return;
  } else if ( a == b ) {
    lm = rm = 1; ln = rn = 1;
    return ;
  }
  lm = 0; ln = 1; rm = 1; rn = 1;
  while ( true ) {
    // a / b strictly enclosed in (( lm / ln ,  rm / rn )
    LL cm = lm + rm, cn = ln + rn;
    if ( cn > MAX ) return;
    if ( a * cn - b * cm == 0 ) {
      lm = rm = cm; ln = rn = cn;
      return;
    } else if ( a * cn - b * cm < 0 ) {
      rn = cn; rm = cm;
    } else {
      ln = cn; lm = cm;
    }
  }
}

int main() {
  LL a, b, lm, ln, rm, rn;
  while ( cin >> a >> b >> MAX ) { 
    rational_approx( a, b, lm, ln, rm, rn );
    printf( "%lld/%lld <= %lld/%lld <= %lld/%lld\n", lm, ln, a, b, rm, rn );
  }
  return 0;
}

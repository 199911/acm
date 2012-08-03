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
#define ULL unsigned long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

LL MAX;

// assume a / b < 1
void rational_approx( LL a, LL b, LL &lm, LL &ln, LL &rm, LL &rn ) {
  lm = 0; ln = 1; rm = 1; rn = 1;
  while ( true ) {
    if ( lm * b == ln * a ) {
      rm = lm; rn = ln;
      break;
    }
    if ( rm * b == rn * a ) {
      lm = rm; ln = rn;
      break;
    }
    LL cm = lm + rm, cn = ln + rn;
    if ( cn > MAX ) break;
    if ( a * cn == b * cm ) {
      lm = rm = cm; ln = rn = cn;
      break;
    } else if ( a * cn < b * cm ) {
      LL s = min( (rn * a - rm * b) / (lm * b - ln * a), ( MAX - rn ) / ln );
      if ( s <= 0 ) break;
      rm = lm * s + rm;
      rn = ln * s + rn;
    } else {
      LL s = min( (ln * a - lm * b) / (rm * b - rn * a), ( MAX - ln ) / rn );
      if ( s <= 0 ) break;
      lm = lm + rm * s;
      ln = ln + rn * s;
    }
  }
}

int main() {
  LL cas = 1, a, b, lm, ln, rm, rn;
  while ( cin >> a >> b >> MAX, a || b || MAX ) { 
    rational_approx( a, b, lm, ln, rm, rn );
    printf( "Case %lld: %lld/%lld %lld/%lld\n", cas++, lm, ln, rm, rn );
  }
  return 0;
}

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

// enumerate f_MAX
int MAX, k;

void dfs( int lm, int ln, int rm, int rn ) {
  int cm = lm + rm, cn = ln + rn;
  if ( cn > MAX ) return;
  dfs( lm, ln, cm, cn );
  //printf( "k = %d\n%d/%d\n", k, cm, cn);
  if ( --k == 0 ) { 
    printf( "%d/%d\n", cm, cn );
  }
  dfs( cm, cn, rm, rn );
}

int main() {
  while ( cin >> MAX >> k ) {
    dfs( 0, 1, 1, 1 );
    if ( k > 0 ) printf( "1/1\n");

  }
  return 0;
}

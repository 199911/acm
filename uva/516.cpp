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
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
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
  string line;

  while ( getline(cin, line) ) {
    istringstream stream(line);
    int p, e;
    int k = 1;
    while( stream >> p && p ) {
      stream >> e;
      REP(i, e) k *= p;
    }

    k--;

    if ( !k ) break;

    int pf[11111], pe[11111], n = 0;
    int r = k;

    memset( pe, 0, sizeof(pe) );

    for( int x = 2; r > 1 && x * x <= k; x++ ) {
      if ( r % x == 0 ) {
        pf[n] = x;
        while ( r % x == 0 ) {
          r /= x;
          pe[n]++;
        }
        n++;
      }
    }

    if ( r > 1 ) {
      pf[n] = r;
      pe[n] = 1;
      n++;
    }

    for( int i = n - 1; i >= 0; i-- ) {
      printf( "%d %d%s", pf[i], pe[i], i == 0 ? "\n" : " " ); 
    }
  }
  return 0;
}

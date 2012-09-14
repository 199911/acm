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

#define N 111111

int a[N], b[N], pa[N], pb[N], n, sf = 0;

int dist( int k ) {
  return (pa[k] - pb[k] - sf) % n;
}

struct comp {
  bool operator()( const int &a, const int &b ) {
    int da = dist(a), db = dist(b);
    return da < db || da == db && a < b;
  }
};

int main() {
  scanf( "%d", &n );
  REP( i, n ) { 
    scanf( "%d", &a[i] );
    a[i]--;
    pa[a[i]] = i;
  }
  REP( i, n ) {
    scanf( "%d", &b[i] );
    b[i]--;
    pb[b[i]] = i;
  }
  
  multiset<int, comp> T;
  REP( i, n ) T.insert( i );

  pa[n] = pb[n] = 0;

  REP( i, n ) {
    int x = *T.upper_bound( n ), y = *T.lower_bound( n );
    int ans = min( abs(dist(x)), abs(dist(y)) );
    printf( "%d\n", ans );
    int ch = b[n - 1 - i];
    T.erase( ch );
    sf++;
    pb[n]++;
    T.insert( ch );
  }
  return 0;
}

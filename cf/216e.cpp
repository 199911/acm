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

LL nn( LL x, LL m ) {
  if ( x == 0 ) return 0;
  x = ( x % m + m ) % m;
  if ( x == 0 ) return m;
  return x;
}

LL mm( LL x, LL m ) {
  return ( x % m + m ) % m;
}

int main() {
  LL n, k, b;
  LL ps = 0, ans = 0, cnt[111111], ls = -1;
  map<LL, LL> MP;

  cin >> k >> b >> n;

  MP[0] = 1;
  REP( i, n ) {
    LL x;
    cin >> x;
    ps += x;

    if( x == 0 ) {
      if ( ls == -1 ) ls = i;
    } else {
      ls = -1;
    }

    if ( b == 0 ) {
      cnt[i] = ls == -1 ? 0 : i - ls + 1;
    } else {
      if ( ls > 0 ) cnt[i] = cnt[ls - 1];
      else if ( ls == 0 ) cnt[i] = 0;
      else {
        LL y = mm( ps - b, k - 1 );
        if ( MP.find( y ) == MP.end() ) cnt[i] = 0;
        else cnt[i] = MP[y];
      }
    }

    if ( MP.find( ps % (k - 1) ) != MP.end() ) {
      MP[ ps % (k - 1) ] = MP[ ps % (k - 1) ] + 1;
    } else {
      MP[ ps % (k - 1) ] = 1;
    }

    ans += cnt[i];
  }

  cout << ans << endl;

  return 0;
}

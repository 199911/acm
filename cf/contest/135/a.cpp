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

int main() {
  int cnt[222], k;
  string in;
  CLR( cnt, 0 );
  cin >> k >> in;
  REP( i, in.length() ) {
    cnt[in[i]]++;
  }

  int ok = 1;
  string out;
  FOE( i, 'a', 'z' ) {
    if ( cnt[i] % k ) ok = 0;
    cnt[i] /= k;
    REP( j, cnt[i] ) out.append( 1, (char)i );
  }

  if ( ok ) {
    REP( i, k ) cout << out;
    cout << endl;
  } else {
    puts( "-1" );
  }

  return 0;
}

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
  LL x = 0, cnt = 0, p, d, l, u;
  cin >> p >> d;
  l = p - d;
  u = p;
  LL mx = 0, mp;

  for( LL i = 0; i <= 18 && x <= u; i++ ) {
    LL px = (u - x) / (x + 1);
    LL dx = (l - x) / ( x + 1 );
    LL r = (l - x) % (x + 1);

    if ( r > 0 ) dx++;
    else if ( r < 0 ) dx--;

    if ( px >= dx ) {
      mx = x;
      mp = x + px * ( x + 1 );
    }
    x *= 10;
    x += 9;
  }
  cout << mp << endl;
  return 0;
}

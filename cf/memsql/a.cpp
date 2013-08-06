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

string s;
int cnt[999], l, tp;

bool doit( int k ) {
  int tot = 0;
  FOE(i, 'a', 'z' ) tot += ( cnt[i] + k - 1 ) / k;
  return tot <= l;
}

int main() {
  cin >> s >> l;
  CLR( cnt, 0 );
  tp = 0;
  REP( i, s.length() ) {
    cnt[s[i]]++;
  }
  FOE( i, 'a', 'z' ) if ( cnt[i] ) tp++;
  if ( tp > l ) puts( "-1" );
  else {
    if ( s.length() <= l ) {
      puts( "1" );
      printf( s.c_str() );
      REP( i, l - s.length() ) printf( "a" );
      puts( "" );
    } else {
      int lo = 1, hi = s.length();
      while( lo < hi - 1 ) {
        int mid = ( lo + hi ) / 2;
        if ( doit( mid ) ) {
          hi = mid;
        } else {
          lo = mid;
        }
      } 
      cout << hi << endl;
      int rem = l, k = hi;
      FOE( i, 'a', 'z' ) {
        REP( j, ( cnt[i] + k - 1 ) / k ) {
          cout << (char)i;
          rem--;
        }
      }
      while( rem ) {
        cout << "a";
      }
      puts( "" );
    }
  }
  return 0;
}

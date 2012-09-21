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

char str[N];
int cnt[N], st[N], sn, n, dp[N], fst;

int main() {
  sn = 0;
  scanf( "%s", str );
  n = strlen( str );

  REP( i, n ) {
    if ( str[i] == '(' ) {
      st[sn++] = i;
      dp[i] = -1;
    } else if ( str[i] == '[' ) {
      st[sn++] = i;
      dp[i] = -1;
    } else if ( str[i] == ')' ) {
      if ( sn > 0 && str[st[sn - 1]] == '(' ) {
        sn--;
        dp[i] = st[sn];
      } else {
        sn = 0;
        dp[i] = -1;
      }
    } else {
      if ( sn > 0 && str[st[sn - 1]] == '[' ) {
        sn--;
        dp[i] = st[sn];
      } else {
        sn = 0;
        dp[i] = -1;
      }
    }
  }

  CLR( cnt, 0 );
  cnt[0] = str[0] == '[';
  FOR( i, 1, n ) cnt[i] = cnt[i - 1] + ( str[i] == '[' );

  int st = -1, en = -1, mx = 0;
  REP( i , n )  {
    if ( dp[i] != -1 ) {
      if ( dp[i] > 0 && dp[dp[i] - 1] != -1 ) dp[i] = dp[dp[i] - 1];
      int a = dp[i], b = i, c = cnt[b] - ( a == 0 ? 0 : cnt[a - 1] ); 
      if ( c > mx ) {
        mx = c; st = a; en = b;
      }
    }
  }

  printf( "%d\n", mx );
  if ( mx ) {
    FOE( i, st, en ) printf( "%c", str[i] );
    puts( "" );
  }

  return 0;
}

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
int a[555555];
int dp[2][26], pi[500001][26];

int main() {
  int n, k;
  string str;
  cin >> n >> k >> str;
  REP( i, n ) a[i] = str[i] - 'A';

  REP( i, k ) dp[0][i] = a[0] != i;

  for( int i = 1; i < str.length(); i++ ) {
    int s = -1, t = -1, mi = 1<<29;
    REP( j, k ) {
      mi = min( mi, dp[(i - 1) % 2][j] );
    }
    REP( j, k ) {
      if ( dp[(i - 1) % 2][j] == mi ) {
        if ( s == -1 ) s = j;
        else if ( t == -1 ) t == j;
      }
    }
    if ( s != -1 && t != -1 ) {
      REP( j, k ) {
        dp[i%2][j] = mi + !(a[i] == j);
        pi[i][j] = j == t ? s : t;
      }
    } else if ( s != -1 ) {
      REP( j, k ) {
        if ( j != s ) {
          dp[i%2][j] = mi + (a[i] != j);
          pi[i][j] = s;
        }
        else {
          dp[i%2][j] = 1<<29;
          REP( x, k ) {
            if ( x != j ) 
              dp[i%2][j] = min( dp[(i-1)%2][x], dp[i%2][j] );
          }
          REP( x, k ) {
            if ( x != j && dp[i%2][j] == dp[(i - 1)%2][x] ) pi[i][j] = x;
          }
          dp[i%2][j] += j != a[i];
        }
      }
    }
//    REP( j, k ) printf( "dp[%d][%d] = %d\n", i, j , dp[i%2][j]);
  }
  int ans = 1<<29;
  REP( i, k ) ans = min( ans , dp[(n-1)%2][i] );
  cout << ans << endl;
  int ptr = -1;
  REP( i, k ) {
    if( dp[(n - 1)%2][i] == ans ) ptr = i;
  }
  int out[555555];
  for( int x = n - 1; x >= 0; x-- ) {
    out[x] = ptr;
    ptr = pi[x][ptr];
  }
  REP( i, n ) {
    printf( "%c", 'A' + out[i] );
  }
  puts( "" );
  
  return 0;
}

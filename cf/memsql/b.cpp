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

#define N 3333

string s;
int cnt[222], n;
int dp[N][N], p[N][N];

void print( int i, int j ) {
  if ( i > j ) return;
  if ( i == j || p[i][j] == 0 ) {
    printf( "%c", s[i] );
    return;
  }
  if ( p[i][j] == 3 ) {
    printf( "%c", s[i] );
    print( i + 1, j - 1 );
    printf( "%c", s[j] );
  } else if ( p[i][j] == 2 ) {
    print( i, j - 1 );
  } else if ( p[i][j] == 1 ) {
    print( i + 1, j );
  } else while( 1 );
}

int main() {
  cin >> s;
  n = s.length();
  if ( s.length() > N ) {
    CLR( cnt, 0 );
    REP( i, s.length() ) {
      cnt[s[i]]++;
    }
    FOE( c, 'a', 'z' ) {
      if ( cnt[c] >= 100 ) {
        REP( i, 100 ) printf( "%c", c );
        puts( "" );
        break;
      }
    }
  } else {
    CLR( p, 0 );
    CLR( dp, 0 );
    REP( i, n ) dp[i][i] = 1;
    FOE( l, 2, n ) {
      FOE( i, 0, n - l ) {
        int j = i + l - 1;
        if ( s[i] == s[j] ) {
          dp[i][j] = dp[i + 1][j - 1] + 2; 
          p[i][j] = 3;
        } else {
          if ( dp[i + 1][j] < dp[i][j - 1] ) {
            dp[i][j] = dp[i][j - 1];
            p[i][j] = 2;
          } else {
            dp[i][j] = dp[i + 1][j];
            p[i][j] = 1;
          }
        }
      }
    }

    if ( dp[0][n - 1] >= 100 ) {
      REP( i, n ) {
        FOR( j, i + 1, n ) {
          if ( dp[i][j] == 100 ) {
            print( i, j );
            puts( "" );
            goto bye;
          }
        }
      }
      while( 1 );
bye:{}
    } else {
      print( 0, n - 1 );
      puts( "" );
    }
  }
  return 0;
}

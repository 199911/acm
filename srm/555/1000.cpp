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

struct MapGuessing {
  string code, goal;
  LL cnt[100][100];
  map<LL, LL> MP[100];
  int n;

  LL count( int st, LL rw ) {
    if ( st == n - 1 ) {
      int a = 0, b = 0;
      REP( i, n )
        if ( rw & ( 1LL << i ) ) {
          if ( cnt[i][st] == 2 ) a = 1, b = 1;
          else if ( cnt[i][st] == 1 ) b = 1;
          else if ( cnt[i][st] == 0 ) a = 1;
        }
      return a + b;
    } else {
      LL ra = 0, rb = 0;
      REP( i, n )
        if ( rw & ( 1LL << i ) ) {
          if ( cnt[i][st] == 2 ) { ra |= 1ll << i; rb |= 1ll << i; }
          else if ( cnt[i][st] == 1 ) { ra |= 1ll <<i; }
          else if ( cnt[i][st] == 0 ) { rb |= 1ll <<i; }
          else puts( "shit" );
        }
      LL ans = 0;
      if ( ra ) ans += count( st + 1, ra );
      if ( rb ) ans += count( st + 1, rb );
      return ans;
    }
  }

  void attemp( int s ) {
    CLR( cnt[s], -1 );
    int ptr = s;
    for( int i = 0; i < code.length(); i++ ) {
      if ( code[i] == '<' ) ptr--;
      else if ( code[i] == '>' ) ptr++;
      if ( ptr >= goal.length() || ptr < 0 ) return;
    }
    ptr = s;
    int rec[100], ct = 0;
    for( int i = 0; i < goal.length(); i++ )
      rec[i] = cnt[s][i] = goal[i] - '0';
    for( int i = 0; i < code.length(); i++ ) {
      if( code[i] == '<' ) ptr--;
      else if ( code[i] == '>' ) ptr++;
      else if ( code[i] == '0' ) {
        if ( goal[ptr] == '0' ) { 
          if ( cnt[s][ptr] == -1 ) ct--;
          cnt[s][ptr] = 2;
        } else { 
          if ( cnt[s][ptr] != -1 ) ct++;
          cnt[s][ptr] = -1;
        }
      } else if ( code[i] == '1' ) {
        if ( goal[ptr] == '1' ) { 
          if ( cnt[s][ptr] == -1 ) ct--;
          cnt[s][ptr] = 2;
        }
        else { 
          if ( cnt[s][ptr] != -1 ) ct++;
          cnt[s][ptr] = -1;
        }
      }
      if ( ct == 0 ) {
        REP( i, n ) rec[i] = cnt[s][i];
      } 
    }
    REP( i, n ) cnt[s][i] = rec[i];
  }

  LL countPatterns( string Goal, vector<string> Code ) {
    goal = Goal;
    n = goal.length();
    code.clear();
    for( vector<string>::iterator it = Code.begin(); it != Code.end(); it++ )
      code.append( *it );
    puts( code.c_str() );
    for( int i = 0; i < n; i++ )
      attemp(i);
    LL ans = 0, fl = 0;
    REP( i, n ) {
      REP( j, n ) {
        if ( cnt[i][j] == -1 ) printf( "_" );
        else if ( cnt[i][j] == 2 ) printf( "*" );
        else printf( "%lld", cnt[i][j] );
      }
      puts( "" );
    }
    REP( i, n ) {
      int ok = 1;
      REP( j, n ) if ( cnt[i][j] == -1 ) ok = 0;
      if( ok ) fl |=  1LL << i;
    }
    ans = count( 0, fl );
    return ans;
  }
};


int main() {
  return 0;
}

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

string a[55], b[55], mt[55][55], t;
bool mtch[55][55], us[55];
int m, n, l, T, cas, cur, seq[55][55];

bool comp( const int &x, const int &y ) {
  if ( mtch[cur][x] && mtch[cur][y] ) return mt[cur][x] < mt[cur][y];
  else {
    if ( !( mtch[cur][x] || mtch[cur][y] ) ) return x < y;
    else return mtch[cur][x];
  }
}

bool find( string x, string y, string &ans ) {
  int n = x.length();
  ans = x;
  REP( i, n ) {
    if ( x[i] != '?' && y[i] != '?' ) {
      if ( x[i] != y[i] ) {
        ans.clear();
        return false;
      }
    } else {
      if ( x[i] == '?' && y[i] != '?' ) {
        ans[i] = y[i];
      } else if ( x[i] != '?' && y[i] == '?' ) {
        ans[i] = x[i];
      } else {
        ans[i] = 'a';
      }
    }
  }
  return true;
}

pair<bool,string> dfs( int x ) {
  if ( x == m ) {
    pair<bool,string> ret;
    ret.first = true;
    ret.second.clear();
    return ret;
  }
  for( int i = 0; i < m; i++ ) {
    //printf( "mtch[%d][%d] = %d\n", x, seq[x][i], mtch[x][seq[x][i]] );
    if ( mtch[x][seq[x][i]] ) {
      if ( !us[seq[x][i]] ) {
        us[seq[x][i]] = 1;
        pair<bool,string> ans = dfs( x + 1 );
        us[seq[x][i]] = 0;
        if ( ans.first ) {
          ans.second.append( mt[x][seq[x][i]] );
          return ans;
        }
      }
    } else {
      break;
    }
  }
  pair<bool,string> ret;
  ret.first = false;
  ret.second.clear();
  return ret;
}

int main() {
  scanf( "%d", &T );
  FOE( cas, 1, T ) {
    scanf( "%d", &m );
    REP( i, m) REP( j, m ) mt[i][j].clear();
    CLR( mtch, 0 );
    cin >> t;
    n = t.length();
    l = n / m;
    REP( i, m ) {
      a[i] = t.substr( i * l, l );
    }
    cin >> t;
    REP( i, m ) b[i] = t.substr( i * l, l );
    REP( i, m ) REP( j, m ) {
      mtch[i][j] = find( a[i], b[j], mt[i][j] );
    }
    REP( i, m ) REP( j, m ) seq[i][j] = j;
    /*
    REP( i, m ) {
      REP( j, m ) {
        printf( "%d:%s\t", mtch[i][j], mt[i][j].c_str() );
      }
      puts( "" );
    }
    */
    REP( i, m ) {
      cur = i;
      sort( seq[i], seq[i] + m, comp );
//      printf( "%d:", i );
//      REP( j, m ) printf( " %d", seq[i][j] );
//      puts( "" );
    }
    CLR( us, 0 );
    pair<bool,string> ans = dfs( 0 );
    printf( "Case #%d: ", cas );
    if ( ans.first ) {
      string tmp = ans.second, sol;
      sol.clear();
      REP( i, m ) sol.append( tmp.substr( n - ( i + 1 ) * l, l ) );

      printf( "%s\n", sol.c_str() );
    } else {
      puts( "IMPOSSIBLE" );
    }
  }
  return 0;
}

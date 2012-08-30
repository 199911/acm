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

#define N 222222

int rt[N], lf[N], n, pk[N];

int dis( int st ) {
  if ( st == 1 && rt[st] == n ) return 1<<29;
  else if ( st == 1 ) return rt[st] - 1;
  else if ( rt[st] == n ) return rt[st] - st;
  else {
    int pos = ( rt[st] + st ) / 2;
    return pos - st;
  }
}

struct comp {
  bool operator() ( const int &a, const int &b ) const {
    int sa = dis( a ), sb = dis( b );
    if ( sa == sb ) return a < b;
    return sa > sb;
  }
};

set<int, comp> T;
map<int, int> mp;

int main() {
  CLR( lf, -1 );
  CLR( rt, -1 );
  CLR( pk, 0 );
  int k;
  scanf( "%d%d", &n, &k );
  rt[1] = n; 
  lf[n] = 1;
  T.insert( 1 );

  REP( i, k ) {
    int op, id;
    scanf( "%d%d", &op, &id );
    if( op == 1 ) {
      //puts( "----------------" );
      int l = *T.begin();
      int r = rt[l];
      int pos = -1;

      if ( l == 1 && r == n ) pos = 1;
      else if ( l == 1 ) pos = 1;
      else if ( r == n ) pos = n;
      else pos = (l + r) / 2;

      pk[pos] = 1;
      mp[id] = pos;
      
      T.erase( T.begin() );

      if ( pos > l ) {
        rt[l] = pos - 1;
        lf[pos - 1] = l;
        T.insert( l );
      }
      if ( pos < r ) { 
        rt[pos + 1] = r;
        lf[r] = pos + 1;
        T.insert( pos + 1 );
      }

      printf( "%d\n", pos );
    } else {
      //puts( "--------------" );
      int x = mp[id];
      //printf( "%d out\n", x );
      int l = x, r = x;
      if( x > 1 && !pk[x - 1] ) {
        //if ( T.find( l ) == T.end() ) puts( "aaaa" );
        l = lf[x - 1];
        T.erase( l );
        lf[x - 1] = -1;
        rt[l] = -1;
      }
      if ( x < n && !pk[x + 1] ){
        if ( T.find( x + 1 ) == T.end() ) puts( "asdf" );
        T.erase( x + 1 );
        r = rt[x + 1];
        lf[r] = -1;
        rt[x + 1] = -1;
      }
      rt[l] = r;
      lf[r] = l;
      T.insert( l );
      mp.erase( id );
      pk[x] = 0;
      /*
      for( set<int,comp>::iterator it = T.begin(); it != T.end(); it++ ) {
        printf( "[%d, %d] ", *it, rt[*it] );
      }
      puts( "" );
      */
    }
  }

  return 0;
}

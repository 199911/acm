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
#include <vector>
#include <list>
#include <set>
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
#define abs(x) ((x)<0?-(x):(x))
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

struct P {
  LL x, y;
  P() {}
  P( LL x, LL y ): x(x), y(y) {}
  void eat() { scanf( "%lld%lld", &x, &y ); }
};

bool comp_x( const P &a, const P &b ) {
  return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool comp_y( const P &a, const P &b ) {
  return a.y < b.y || a.y == b.y && a.x < b.x;
}

#define N ((1<<18)+20)

P B[N];
vector<P> ST[N];
int L[N], R[N], n;
LL xmx, xmn, ymx, ymn;

void output( vector<P> V ) {
  printf( "[" );
  for( vector<P>::iterator it = V.begin(); it != V.end(); it++ ) 
    printf( "(%lld, %lld) ", it->x, it->y );
  puts( "]" );
}

void init( int p, int l, int r ) {
  if ( l == r ) { 
    ST[p].clear();
    ST[p].reserve( 1 );
    ST[p].push_back( B[l] );
    L[p] = l;
    R[p] = r;
  } else {
    int m = (l + r) >> 1;
    init( p * 2, l, m );
    init( p * 2 + 1, m + 1, r );

    L[p] = l; R[p] = r;
    ST[p].clear();
    ST[p].reserve( r - l + 1 );
    ST[p].insert( ST[p].end(), ST[2 * p].begin(), ST[2 * p].end() );
    vector<P>::iterator mid = ST[p].end();
    ST[p].insert( ST[p].end(), ST[2 * p + 1].begin(), ST[2 * p + 1].end() );
    inplace_merge( ST[p].begin(), mid, ST[p].end(), comp_y );
  }

}

LL ask( vector<P> V, P p ) {
  vector<P>::iterator it = lower_bound( V.begin(), V.end(), p, comp_y );
  LL ans = it->y - p.y;
  if ( it != V.begin() ) { 
    it--;
    ans = min( ans, p.y - it->y );
  }
  return ans;
}

LL query( int p, int l, int r, P q ) {
  if ( L[p] > r || R[p] < l ) return 1LL<<60;
  else if ( l <= L[p] && r >= R[p] ) return ask( ST[p], q );
  else return min( query( p * 2, l, r, q ), query( p * 2 + 1, l, r, q ) );
}

bool search( P q, LL rad ) {
  P rt = P( q.x + rad, (1LL << 60) ), lf = P( q.x - rad, -(1LL << 60) );
  if ( lf.x > B[n - 1].x ) return true;
  if ( rt.x < B[0].x ) return true;
  
  int r, l;
  l = lower_bound( B, B + n, lf, comp_x ) - B;
  r = upper_bound( B, B + n, rt, comp_x ) - B - 1;

  LL len = query( 1, l, r, q );
  if ( len > rad ) return true;
  else return false;
}

LL find( P q ) {
  if ( !search( q, 0 ) ) return 0;
  
  LL lo = 0, up = max( max( abs( xmx - q.x ), abs( xmn - q.x ) ), max( abs( ymx - q.y ), abs( ymn - q.y ) ) );
  while( up > lo + 1) {
    LL mid = ( up + lo ) >> 1;
    if ( search( q, mid ) ) lo = mid;
    else up = mid;
  }

  return up;
}

int main() {
  int flag = 0;
  while( scanf( "%d", &n ), n > 0 ) {
    LL a, b;

    xmx = ymx = -1LL<<32;
    xmn = ymn = 1LL<<32;
    REP( i, n ) {
      scanf( "%lld%lld", &a, &b );
      B[i] = P( a + b, a - b );
      xmx = max( xmx, a + b );
      xmn = min( xmn, a + b );
      ymx = max( ymx, a - b );
      ymn = min( ymn, a - b );
    }
    sort( B, B + n, comp_x );
    
    init( 1, 0, n - 1 );

    if ( flag ) puts( "" );
    flag = 1;

    int Q;
    scanf( "%d", &Q );
    REP( i, Q ) {
      scanf( "%lld%lld", &a, &b );
      P q = P( a + b, a - b );
      printf( "%lld\n", find( q ) );
    }
  }
  return 0;
}

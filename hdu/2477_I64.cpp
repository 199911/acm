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
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define ABS(a) ((a)>0?(a):-(a))
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<30)
#define LL long long
#define ULL unsigned long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

#define EPS 1e-9
#define feq(a,b) (fabs((a)-(b))<EPS)
#define fgt(a,b) ((a)>(b)+EPS)
#define fge(a,b) ((a)>(b)-EPS)
#define flt(a,b) ((a)<(b)-EPS)
#define fle(a,b) ((a)<(b)+EPS)

struct P {
	LL x, y;
	P() {}
	P( LL x, LL y ): x(x), y(y) {}
	void eat() { scanf( "%I64d%I64d", &x, &y ); }

	P operator+( P p ) { return P( x + p.x, y + p.y ); }
	P operator-( P p ) { return P( x - p.x, y - p.y ); }
	P operator*( double s ) { return P( x * s, y * s ); }
	LL operator*( P p ) { return x * p.x + y * p.y; }
	LL operator^( P p ) { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return x == p.x &&  y == p.y; }

	double mag() { return sqrt( (double)( x * x + y * y) ); }
	LL mag2() { return x * x + y * y; }

	P nor() { return * this * ( 1.0 / mag() ); }

	P rot() { return P( -y, x ); }
	P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
	P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

double area(P a, P b, P c) {
	return 0.5 * ( ( b - a ) ^ ( c - a ) );
}

bool ccw( P a, P b, P c ) {
  return fge( area( a, b, c ), 0.0 );
}

bool Ccw( P a, P b, P c ) {
  return fgt( area( a, b, c ), 0.0 );
}

LL curY;

struct E {
  P c;
  LL r;
  int cid;
  bool open;

  E() {}
  E( P c, LL r, int cid, bool open ): c(c), r(r), cid(cid), open(open) {}

  double getX( LL curY ) const {
    double t = sqrt( SQR(r) - SQR(curY - c.y) + EPS );
    double x = open ? c.x - t : c.x + t;
    return x;
  }

  bool operator<( const E &e ) const {
    double s = getX( curY ), t = e.getX( curY );
    return s < t - EPS || s < t + EPS && open > e.open;
  }
};

#define N 55555

P C[N];
LL R[N], V[N];
int n, k;

bool comp_evt( const int &a, const int &b ) {
  P d = P( 0.0, 1.0 );
  P pa = a > 0 ? C[a] + d * R[a] : C[-a] - d * R[-a];
  P pb = b > 0 ? C[b] + d * R[b] : C[-b] - d * R[-b];

  if ( pa.y != pb.y ) return pa.y > pb.y;
  if ( a > 0 ^ b > 0 ) return a > 0;
  if ( pa.x != pb.x ) return pa.x < pb.x;
  if ( R[abs(a)] != R[abs(b)] ) R[abs(a)] > R[abs(b)];
  return abs(a) < abs(b);
}

int hd[N], nt[N], to[N], p[N], en, root;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
  root = 0;
}

void add( int a, int b ) {
//  printf( "add %d %d\n", a, b );
  to[en] = b; nt[en] = hd[a]; p[b] = a; hd[a] = en++;
}

// a enclose b
bool enclose( P a, LL ra, P b, LL rb ) {
  if ( ra <= rb ) return false;
  return fle( (b - a).mag2(), SQR(ra - rb) );
}

bool enclose_idx( int a, int b ) {
  return enclose( C[a], R[a], C[n], R[b] );
}

set<E> T;
typedef set<E>::iterator SIT;

SIT pred( SIT it ) { return it == T.begin() ? it : --it; }
SIT succ( SIT it ) { return it == T.end() ? it : ++it; }

void sweep() {
  int q[N * 2], m = 0;
  FOE( i, 1, n ) {
    q[m++] = i;
    q[m++] = -i;
  }

  sort( q, q + m, comp_evt );
  init();
  T.clear();

  REP( i, m ) {
    if ( q[i] > 0 ) {
      E e1 = E( C[q[i]], R[q[i]], q[i], 1), e2 = E( C[q[i]], R[q[i]], q[i], 0 );

      curY = C[q[i]].y + R[q[i]];

      SIT pit = T.lower_bound( e1 );

      if ( pit == T.end() ) {
        add( root, q[i] );
      } else {
        if ( !pit->open ) {
          add( pit->cid, q[i] );
        } else {
          add( p[pit->cid], q[i] );
        }
      }

      T.insert( e1 );
      T.insert( e2 ); 
    } else if ( q[i] < 0 ) {
      E e1 = E( C[-q[i]], R[-q[i]], -q[i], 1), e2 = E( C[-q[i]], R[-q[i]], -q[i], 0 );
      curY = C[-q[i]].y - R[-q[i]];

      SIT cit = T.find( e1 ), ccit = T.find( e2 );
      T.erase( cit ), T.erase( ccit );
    } 
  }
}

LL ans = 0;
LL *mi[N], *ma[N], sma[N], smi[N];
int dp[N], sz[N];

void dfs( int x ) {
  dp[x] = 0;
  if ( x != root ) sma[x] = smi[x] = V[x];
  else sma[x] = -INF, smi[x] = INF;

  for ( int e = hd[x]; e != -1; e = nt[e] ) {
    dfs( to[e] );
    dp[x] = max( dp[to[e]] + 1, dp[x] );
    sma[x] = max( sma[x], sma[to[x]] );
    smi[x] = min( smi[x], smi[to[x]] );
  }

  if ( x != root ) {
    ans = max( ans, V[x] - smi[x] );
    ans = max( ans, sma[x] - V[x] );
  }

  sz[x] = min( k, dp[x] ) + 1;

  mi[x] = (LL *) malloc( sz[x] * sizeof( LL ) );
  ma[x] = (LL *) malloc( sz[x] * sizeof( LL ) );

  if ( x == root ) {
    mi[x][0] = INF; 
    ma[x][0] = -INF;
  } else {
    mi[x][0] = ma[x][0] = V[x];
  }

  FOR( i, 1, sz[x] ) {
    mi[x][i] = mi[x][i - 1];
    ma[x][i] = ma[x][i - 1];

    for ( int e = hd[x]; e != -1; e = nt[e] ) {
      if ( i - 1 < sz[to[e]] ) {
        mi[x][i] = min( mi[x][i], mi[to[e]][i - 1] );
        ma[x][i] = max( ma[x][i], ma[to[e]][i - 1] );
      }
    }
  }

#ifdef DEBUG
  REP( i, sz[x] ) {
    printf( "ma[%d][%d] = %d\n ", x, i, ma[x][i] );
    printf( "mi[%d][%d] = %d\n ", x, i, mi[x][i] );
  }
#endif

  if ( x == root ) {
    FOR( i, 1, k ) {
      int p = min( sz[x] - 1, i ), q = min( sz[x] - 1, k - i );
      ans = max( ans, ma[x][p] - mi[x][q] );
    }
  } else {
    FOE( i, 0, k ) {
      int p = min( sz[x] - 1, i ), q = min( sz[x] - 1, k - i );
      ans = max( ans, ma[x][p] - mi[x][q] );
    }
  }

  for ( int e = hd[x]; e != -1; e = nt[e] ) {
    free( ma[to[e]] );
    free( mi[to[e]] );
  }
}

int main() {
  int Cas;
  scanf( "%d", &Cas );
  FOE( cas, 1, Cas ) {
    scanf( "%d%d", &n, &k );
    FOE( i, 1, n ) {
      C[i].eat(); 
      scanf( "%I64d%I64d", &R[i], &V[i] );
    }

    sweep();

    ans = 0;
    dfs( root );

    printf( "Case %d: %I64d\n", cas, ans );
  }
	return 0;
}

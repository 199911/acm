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
#define ABS(a) ( (a) >= 0LL ? (a) : -(a) )
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1LL<<40)
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
	void eat() { scanf( "%lld%lld", &x, &y ); }

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

#define N 55555

P C[N];
LL R[N], V[N];
int n, K;
LL curY;

struct E {
  int cid;
  bool open;

  E() {}
  E( int cid, bool open ): cid(cid), open(open) {}

  double getX( LL now ) const {
    P c = C[cid]; 
    LL r = R[cid];
    
    if ( ABS( c.y - now ) > r ) while ( 1 );

    double t = sqrt( SQR(r) - SQR(now - c.y) + EPS );
    double x = open ? c.x - t : c.x + t;
    return x;
  }

  bool operator<( const E &e ) const {
    double x1 = getX( curY ), x2 = e.getX( curY );
    return x1 < x2 - EPS || x1 < x2 + EPS && open > e.open;
  }
};


bool comp_evt( const int &a, const int &b ) {
  LL ya, yb;
  ya = a > 0 ? C[a].y + R[a] : C[-a].y - R[-a];
  yb = b > 0 ? C[b].y + R[b] : C[-b].y - R[-b];

  if ( ya != yb ) return ya > yb;
  return a > b;
}

int hd[N], nt[N], to[N], p[N], en, root;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  en = 0;
  root = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; p[b] = a; hd[a] = en++;
}

set<E> T;
typedef set<E>::iterator SIT;

void sweep() {
  int q[N * 2], m = 0;

  curY = 1LL << 40;

  FOE( i, 1, n ) {
    q[m++] = i;
    q[m++] = -i;
  }

  sort( q, q + m, comp_evt );

  init();
  T.clear();

  REP( i, m ) {
    if ( q[i] > 0 ) {
      int v = q[i];
      E e1 = E( v, 1 ), e2 = E( v, 0 );
      LL nxt = C[v].y + R[v];
      curY = nxt;

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
      int v = -q[i];
      E e1 = E( v, 1 ), e2 = E( v, 0 );
      LL nxt = C[v].y - R[v];
      curY = nxt;

      SIT cit = T.find( e1 ), ccit = T.find( e2 );
      T.erase( cit ); 
      T.erase( ccit );
    } 
  }
}

LL ans = 0;
LL *mi[N], *ma[N];
int sz[N];

void dfs( int x ) {
  sz[x] = 1;
  for ( int e = hd[x]; e != -1; e = nt[e] ) {
    dfs( to[e] );
    sz[x] = max( sz[x], sz[to[e]] + 1 );
  }

  if ( sz[x] > K + 1) sz[x] = K + 1;

  ma[x] = ( LL * ) malloc ( sz[x] * sizeof( LL ) );
  mi[x] = ( LL * ) malloc ( sz[x] * sizeof( LL ) );

  if ( x == root ) {
    REP( i, sz[x] ) {
      mi[x][i] = INF; 
      ma[x][i] = -INF;
    }
  } else {
    REP( i, sz[x] ) mi[x][i] = ma[x][i] = V[x];
  }

  for ( int e = hd[x]; e != -1; e = nt[e] ) {
    int y = to[e];
    for ( int i = 1; i < min( sz[y] + 1, sz[x] ); i++ ) {
      if ( mi[x][i] > mi[y][i - 1] ) mi[x][i] = mi[y][i - 1]; 
      if ( ma[x][i] < ma[y][i - 1] ) ma[x][i] = ma[y][i - 1]; 
    }
  }

  REP( i, sz[x] - 1 ) {
    if ( ma[x][i] > ma[x][i + 1] ) ma[x][i + 1] = ma[x][i];
    if ( mi[x][i] < mi[x][i + 1] ) mi[x][i + 1] = mi[x][i];
  }

  REP( i, sz[x] ) {
    ans = max( ans, ma[x][i] - mi[x][min( sz[x] - 1, K - i)] );
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
    scanf( "%d%d", &n, &K );
    FOE( i, 1, n ) {
      C[i].eat(); 
      scanf( "%lld%lld", &R[i], &V[i] );
    }

    sweep();

    ans = 0;
    dfs( root );

    printf( "Case %d: %lld\n", cas, ans );
  }
	return 0;
}

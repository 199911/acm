#include <cstdio>
#include <cctype>
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

#define EPS 1e-9
#define feq(a,b) (fabs((a)-(b))<EPS)
#define fgt(a,b) ((a)>(b)+EPS)
#define fge(a,b) ((a)>(b)-EPS)
#define flt(a,b) ((a)<(b)-EPS)
#define fle(a,b) ((a)<(b)+EPS)

struct P {
	double x, y;
	P() {}
	P( double x, double y ): x(x), y(y) {}
	void eat() { scanf( "%lf%lf", &x, &y ); }
	void out() { printf( "(%.1f, %.1f)", x, y ); }

	P operator+( const P &p ) const { return P( x + p.x, y + p.y ); }
	P operator-( const P &p ) const { return P( x - p.x, y - p.y ); }
	P operator*( const double &s ) const { return P( x * s, y * s ); }
	double operator*( const P &p ) const { return x * p.x + y * p.y; }
	double operator^( const P &p ) const { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return feq( x, p.x ) && feq( y, p.y ); }

	double mag() { return sqrt( x * x + y * y ); }
	double mag2() { return x * x + y * y; }

	P nor() { return * this * ( 1.0 / mag() ); }

	P rot() { return P( -y, x ); }
	P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
	P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

bool comp_pnt( const P &a, const P &b ) {
  return !feq( a.y, b.y ) ? fgt( a.y, b.y ) : flt( a.x, b.x ); 
}

bool Ccw( P a, P b, P c ) {
  return ( ( b - a ) ^ ( c - a ) ) > EPS;
}

bool ccw( P a, P b, P c ) {
  return ( ( b - a ) ^ ( c - a ) ) > -EPS;
}

bool btw( P a, P b, P c ) {
  double s = (b - a) * (c - a);
  return feq( (b - a) ^ (c - a), 0.0 ) && s >= -EPS && s <= (c - a).mag2() + EPS;
}

#define N 111111

bool intersect( P a, P b, P c, P d ) {
  if ( feq( (b - a) ^ (d - c), 0.0 ) ) 
    return btw( a, c, b ) || btw( a, d, b ) || btw( c, a, d ) || btw ( c, b, d );
  double s = ((c - a) ^ (d - c)) / ((b - a) ^ (d - c));
  double t = ((a - c) ^ (b - a)) / ((d - c) ^ (b - a));
  if ( fle( 0.0, s ) && fle( s, 1.0 ) && fle( 0.0, t ) && fle( t, 1.0 ) ) return true;
  return false;
}

double curY;

struct E {
  P a, b;   // a should be "above" b
  int open;   // indicate an open paranthesis
  int tid;    // id of triangle
  
  E() {}
  E( P a, P b, int open, int tid ): a(a), b(b), open(open), tid(tid) {}

  double getX( double curY ) const {
    if ( feq( a.y, b.y ) ) return 0.5 * ( a.x + b.x );
    if ( fgt( curY, a.y ) ) return a.y;
    if ( flt( curY, b.y ) ) return b.y;
    return a.x + ( b.x - a.x ) * ( curY - a.y ) / ( b.y - a.y );
  }

  bool operator<( const E &e ) const {
    double x = getX( curY ), ex = e.getX( curY );
    if ( !feq( x, ex ) ) return x < ex;
    if ( tid != e.tid ) return tid < e.tid;
    return open > e.open;
  }
} ed[N * 3];

bool comp_evt( const int &a, const int &b ) {
  P pa = a > 0 ? ed[a].a : ed[-a].b, pb = b > 0 ? ed[b].a : ed[-b].b;
  if ( !feq( pa.y, pb.y ) ) return pa.y > pb.y; 
  if ( a > 0 ^ b > 0 ) return a > 0;
  if ( !feq( pa.x, pb.x ) ) return pa.x < pb.x;
  if ( a > 0 ) return ( ( ed[a].b - ed[a].a ) ^ ( ed[b].b - ed[b].a ) ) > EPS;
  else return ( (ed[-a].a - ed[-a].b ) ^ ( ed[-b].a - ed[-a].b ) ) < -EPS;
}

struct comp_edg {
  bool operator() ( const int &a, const int &b ) {
    return ed[a] < ed[b];
  }
};

bool enclose_1 ( P a, P b, P c, P d ) {
  if ( !Ccw( a, b, c )) swap( a, b );
  return Ccw( a, b, d ) && Ccw( b, c, d ) && Ccw ( c, a, d );
}

bool enclose( P ta, P tb, P tc, P sa, P sb, P sc ) {
  return enclose_1( ta, tb, tc, sa ) && enclose_1( ta, tb, tc, sb ) && enclose_1( ta, tb, tc, sc );
}

set<int, comp_edg> T;
typedef set<int, comp_edg>::iterator SIT;

SIT pred( SIT it ) { return it == T.begin() ? it : --it; }
SIT succ( SIT it ) { return it == T.end() ? it : ++it; } 

// INPUT 
P tri[N][3];
int n, m;

bool enclose_tri( int i, int j ) {
  return enclose( tri[i][0], tri[i][1], tri[i][2], tri[j][0], tri[j][1], tri[j][2] );
}

int hd[N], nt[N], to[N], p[N], root = 0, en;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  root = 0;
  en = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; hd[a] = en++; p[b] = a;
}

bool sweep() {
  // event queue
  int q[N * 3 * 2], qn = 0;
  bool fl[N];
  FOE( i, 1, m ) {
    q[qn++] = i;
    q[qn++] = -i;
  }

  T.clear();
  init();
  CLR( fl, 0 );

  sort( q, q + qn, comp_evt );

#ifdef DEBUG
  REP( i, qn ) {
    printf( "%s(%d): ", q[i] > 0 ? "insert" : "remove", q[i] );
    ed[abs(q[i])].a.out(); 
    ed[abs(q[i])].b.out(); 
    printf( " %d ", ed[abs(q[i])].tid );
    puts( "" );
  }
#endif

  REP( i, qn ) {
    if ( q[i] > 0 ) {
      curY = ed[q[i]].a.y;
      // printf( "curY = %lf\n", curY );
      // insert segments 
      SIT it = T.insert( q[i] ).first;
      SIT pit = pred( it ), sit = succ( it );
      
      E cur = ed[*it];

#ifdef DEBUG
      printf( "curY = %f\n", curY );
      printf("insert: ");
      cur.a.out();
      cur.b.out();
      printf( "(%d)\n", cur.open );

      for( SIT iter = T.begin(); iter != T.end(); iter++ ) {
        E x = ed[*iter];
        printf( "[" );
        x.a.out(); x.b.out(); 
        printf( "(%.1f)", x.getX(curY));
        
        printf( "]" );
      }
      puts( "" );
#endif

      // see if there is intersection
      if ( pit != it && ed[*pit].tid != cur.tid ) {
        E ped = ed[*pit];
        if ( intersect( ped.a, ped.b, cur.a, cur.b ) ) return 0; 
      }

      if ( sit != T.end() && ed[*sit].tid != cur.tid ) {
        E sed = ed[*sit];
        if ( intersect( sed.a, sed.b, cur.a, cur.b ) ) 
          return 0;
      }

      if ( !fl[cur.tid] ) {
        if ( pit == it ) {
          add( root, cur.tid );
        } else {
          if ( enclose_tri( ed[*pit].tid, ed[*it].tid ) ) {
            add( ed[*pit].tid, cur.tid );
          } else {
            add( p[ed[*pit].tid], cur.tid );
          }
        }
      }

      fl[cur.tid] = 1;

    } else {
      curY = ed[-q[i]].b.y;
      SIT it = T.find( -q[i] );
      SIT pit = pred( it ), sit = succ( it );

      E cur = ed[*it];

#ifdef DEBUG
      printf( "curY = %f\n", curY );
      printf( "remove: " );
      cur.a.out();
      cur.b.out();
      printf( "(%d)\n", cur.open );
#endif

      if ( pit != it && sit != T.end() && ed[*sit].tid != ed[*pit].tid ) {
        E ped = ed[*pit], sed = ed[*sit];
        if ( intersect( ped.a, ped.b, sed.a, sed.b ) ) 
          return 0;
      }

      T.erase( it );
    }
  }

  return 1;
}

int d[N];
bool vis[N];

void dfs( int x ) {
  vis[x] = 1;
  for ( int e = hd[x]; e != -1; e = nt[e] ) {
    if ( vis[to[e]] ) continue;
    dfs( to[e] );
    d[x] = max( d[x], d[to[e]] + 1 );
  }
}

int main() {
  int cas = 1;
  while ( scanf( "%d", &n ), n >= 0  ) {
    m = 0;
    FOE( i, 1, n ) {
      REP ( j, 3 ) tri[i][j].eat();
      sort( tri[i], tri[i] + 3, comp_pnt );
      if ( Ccw( tri[i][0], tri[i][1], tri[i][2] ) ) {
        ed[++m] = E( tri[i][0], tri[i][1], 1, i );
        ed[++m] = E( tri[i][1], tri[i][2], 2, i );
        ed[++m] = E( tri[i][0], tri[i][2], 0, i );
      } else {
        ed[++m] = E( tri[i][0], tri[i][1], 1, i );
        ed[++m] = E( tri[i][1], tri[i][2], 0, i );
        ed[++m] = E( tri[i][0], tri[i][2], 2, i );
      }
    }
    if ( sweep() ) {
      FOE( i, 0, n ) d[i] = 1;
      CLR( vis, 0 );
      dfs( root );
      printf( "Case %d: %d shades\n", cas++, d[root] );
    } else {
      printf( "Case %d: ERROR\n", cas++ );
    }
  }
  return 0;
}

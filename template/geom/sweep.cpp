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
    if ( fgt( curY, a.y ) ) return a.x;
    if ( flt( curY, b.y ) ) return b.x;
    return a.x + ( b.x - a.x ) * ( curY - a.y ) / ( b.y - a.y );
  }

  bool operator<( const E &e ) const {
    double x = getX( curY ), ex = e.getX( curY );
    if ( !feq( x, ex ) ) return x < ex;
    if ( open ^ e.open ) return open;
    if ( open ) return ( ( b - a ) ^ ( e.b - e.a ) ) > EPS;
    else return ( ( b - a ) ^ ( e.b - e.a ) ) < -EPS;
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
  return ccw( a, b, d ) && ccw( b, c, d ) && ccw ( c, a, d );
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

bool sweep() {
  // event queue
  int q[N * 3 * 2], qn = 0;
  bool fl[N], ok = 1;
  FOE( i, 1, m ) {
    q[qn++] = i;
    q[qn++] = -i;
  }

  REP( i, n ) fl[i] = 0;

  sort( q, q + qn, comp_evt );

  /*
  REP( i, qn ) {
    printf( "%s(%d): ", q[i] > 0 ? "insert" : "remove", q[i] );
    ed[abs(q[i])].a.out(); 
    ed[abs(q[i])].b.out(); 
    printf( " %d ", ed[abs(q[i])].tid );
    puts( "" );
  }
  */

  REP( i, qn ) {
    if ( q[i] > 0 ) {
      // insert segments 
      SIT it = T.insert( q[i] ).first;
      SIT pit = pred( it ), sit = succ( it );

      E cur = ed[*it];

      // see if there is intersection
      if ( pit != it && ed[*pit].tid != cur.tid ) {
        E ped = ed[*pit];
        if ( intersect( ped.a, ped.b, cur.a, cur.b ) ) {
         ok = 0;
         /*
         printf( "intersect:" );
         ped.a.out();
         ped.b.out();
         cur.a.out();
         cur.b.out();
         printf( "(%d, %d)\n", ped.tid, cur.tid);
         */
        } else {
        }
      }

      if ( sit != T.end() && ed[*sit].tid != cur.tid ) {
        E sed = ed[*sit];
        if ( intersect( sed.a, sed.b, cur.a, cur.b ) ) {
          ok = 0;
          /*
          printf( "intersect:" );
          sed.a.out();
          sed.b.out();
          cur.a.out();
          cur.b.out();
          printf( "(%d, %d)\n", sed.tid, cur.tid );
          */
        } else {
        }
      }

    } else {
      SIT it = T.find( -q[i] );
      SIT pit = pred( it ), sit = succ( it );

      E cur = ed[*it];

      if ( pit != it && sit != T.end() && ed[*sit].tid != ed[*pit].tid ) {
        E ped = ed[*pit], sed = ed[*sit];
        if ( intersect( ped.a, ped.b, sed.a, sed.b ) ) {
          ok = 0;
          /*
          printf( "intersect(%d,%d):", *pit, *sit );
          ped.a.out();
          ped.b.out();
          sed.a.out();
          sed.b.out();
          printf( "(%d, %d)\n", ped.tid, sed.tid);
          */
        }
      }

      T.erase( it );
    }
  }

  return ok;
}

int main() {
  while ( scanf( "%d", &n ), n >= 0  ) {
    m = 0;
    REP( i, n ) {
      REP ( j, 3 ) tri[i][j].eat();
      sort( tri[i], tri[i] + 3, comp_pnt );
      if ( Ccw( tri[i][0], tri[i][1], tri[i][2] ) ) {
        ed[++m] = E( tri[i][0], tri[i][1], 0, i );
        ed[++m] = E( tri[i][1], tri[i][2], 0, i );
        ed[++m] = E( tri[i][0], tri[i][2], 1, i );
      } else {
        ed[++m] = E( tri[i][0], tri[i][1], 1, i );
        ed[++m] = E( tri[i][1], tri[i][2], 1, i );
        ed[++m] = E( tri[i][0], tri[i][2], 0, i );
      }
    }
    if ( sweep() ) {
      puts( "haha" );
    } else {
      puts( "oh no" );
    }
  }
  return 0;
}

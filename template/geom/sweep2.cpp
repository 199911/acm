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
    if ( feq( a.y, b.y ) ) return open ? min( a.x, b.x ) : max( a.x, b.x );
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

set<E> T;
typedef set<E>::iterator SIT;

SIT pred( SIT it ) { return it == T.begin() ? it : --it; }
SIT succ( SIT it ) { return it == T.end() ? it : ++it; } 

// INPUT 
P tri[N][3];
int tp[N], n, m;

bool enclose_tri( int i, int j ) {
  return enclose( tri[i][0], tri[i][1], tri[i][2], tri[j][0], tri[j][1], tri[j][2] );
}

int hd[N], nt[N], to[N], p[N], root = 0, en;

void init() {
  CLR( hd, -1 );
  CLR( nt, -1 );
  root = n;
  en = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; hd[a] = en++; p[b] = a;
}

bool comp_evt( const int &a, const int &b ) {
  P pa = tri[a / 3][a % 3], pb = tri[b / 3][b % 3]; 
  return pa.y == pb.y ? pa.x < pb.x : pa.y > pb.y;
}

bool sweep() {
  int q[N * 3];

  REP( i, n * 3 ) 
    q[i] = i;
  sort( q, q + 3 * n, comp_evt );

  init();
  T.clear();

  REP( evt, 3 * n ) {
    int t = q[evt] / 3, v = q[evt] % 3;
    curY = tri[t][v].y;

    if ( v == 0 ) { // top vertex
      E e1 = ed[t * 3], e2 = ed[t * 3 + 2]; 
      if ( ( (e1.b - e1.a) ^ (e2.b - e2.a)) < -EPS ) swap(e1, e2);
      SIT cit = T.insert( e1 ).first;
      SIT ccit = T.insert( e2 ).first;
      SIT pit = pred( cit );
      SIT sit = succ( ccit );

      pit = pred( cit );
      sit = succ( sit );
      if ( pit != cit && pit->tid != cit->tid && intersect( pit->a, pit->b, cit->a, cit->b ) ) 
        return 0;
      if ( sit != T.end() && sit->tid != cit->tid && intersect( sit->a, sit->b, cit->a, cit->b ) ) 
        return 0;

      pit = pred( ccit );
      sit = succ( ccit );
      if ( pit != ccit && pit->tid != ccit->tid && intersect( pit->a, pit->b, ccit->a, ccit->b ) ) 
        return 0;
      if ( sit != T.end() && sit->tid != ccit->tid && intersect( sit->a, sit->b, ccit->a, ccit->b ) ) 
        return 0;

      pit = pred( cit );
      if ( pit == cit  ) {
        add( root, cit->tid ); 
      } else {
        if ( enclose_tri( pit->tid, cit->tid ) ) {
          add( pit->tid, cit->tid );
        } else {
          add( p[pit->tid], cit->tid );
        }
      }
    } else if ( v == 1 ) {  // transition vertex
      E e1 = ed[t * 3], e2 = ed[t * 3 + 1];
      // error checking
      SIT cit = T.find( e1 );
      SIT pit = pred( cit ), sit = succ( cit );
      if ( pit != cit && sit != T.end() && pit->tid != sit->tid && intersect( pit->a, pit->b, sit->a, sit->b ) ) 
        return 0;
      T.erase( cit );
      
      cit = T.insert( e2 ).first;
      
      pit = pred( cit );
      sit = succ( cit );

      if ( pit != cit && pit->tid != cit->tid && intersect( pit->a, pit->b, cit->a, cit->b ) ) 
        return 0;
      if ( sit != T.end() && sit->tid != cit->tid && intersect( sit->a, sit->b, cit->a, cit->b ) )
        return 0;
    } else  {   // bottom vertex
      E e1 = ed[t * 3 + 1], e2 = ed[t * 3 + 2]; 

      SIT cit = T.find( e1 ), ccit = T.find( e2 );

      if ( cit == T.end() || ccit == T.end() ) while ( 1 );

      SIT pit = pred( cit ), sit = succ( cit );

      if ( pit != cit && pit->tid != cit->tid && intersect( pit->a, pit->b, cit->a, cit->b ) ) 
        return 0;
      if ( sit != T.end() && sit->tid != cit->tid && intersect( sit->a, sit->b, cit->a, cit->b ) ) 
        return 0;

      pit = pred( ccit );
      sit = succ( ccit );

      if ( pit != ccit && pit->tid != ccit->tid && intersect( pit->a, pit->b, ccit->a, ccit->b ) ) 
        return 0;
      if ( sit != T.end() && sit->tid != ccit->tid && intersect( sit->a, sit->b, ccit->a, ccit->b ) ) 
        return 0;

      T.erase( cit );
      T.erase( ccit );
    }

  }

  return 1;
}

int d[N];

void dfs( int x ) {
  for ( int e = hd[x]; e != -1; e = nt[e] ) {
    dfs( to[e] );
    d[x] = max( d[x], d[to[e]] + 1 );
  }
}

void print( int x ) {
  printf( "%d:{", x);
  for ( int e = hd[x]; e != -1; e = nt[e] ) {
    print( to[e] );
    if ( nt[e] != -1 ) printf( ";" );
  }
  printf( "}" );
}

int main() {
  int cas = 1;
  while ( scanf( "%d", &n ), n >= 0  ) {
    m = 0;
    REP( i, n ) {
      REP ( j, 3 ) tri[i][j].eat();
      sort( tri[i], tri[i] + 3, comp_pnt );
      if ( Ccw( tri[i][0], tri[i][1], tri[i][2] ) ) {
        // two left, one right
        tp[i] = 0;
        ed[m++] = E( tri[i][0], tri[i][1], 1, i );
        ed[m++] = E( tri[i][1], tri[i][2], 2, i );
        ed[m++] = E( tri[i][0], tri[i][2], 0, i );
      } else {
        // one left two right
        tp[i] = 1;
        ed[m++] = E( tri[i][0], tri[i][1], 1, i );
        ed[m++] = E( tri[i][1], tri[i][2], 0, i );
        ed[m++] = E( tri[i][0], tri[i][2], 2, i );
      }
    }
    if ( sweep() ) {
      FOE( i, 0, n ) d[i] = 1;
      dfs( root );
      printf( "Case %d: %d shades\n", cas++, d[root] );
    } else {
      printf( "Case %d: ERROR\n", cas++ );
    }
  }
  return 0;
}

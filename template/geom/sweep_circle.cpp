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
  double x, y;
  P() {}
  P( double x, double y ): x(x), y(y) {}
  void eat() { scanf( "%lf%lf", &x, &y ); }
  void out() { printf( "%.1f %.1f ", x, y ); }

  P operator+( P p ) { return P( x + p.x, y + p.y ); }
  P operator-( P p ) { return P( x - p.x, y - p.y ); }
  P operator*( double s ) { return P( x * s, y * s ); }
  double operator*( P p ) { return x * p.x + y * p.y; }
  double operator^( P p ) { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return x == p.x &&  y == p.y; }

  double mag() { return sqrt( (double)( x * x + y * y) ); }
  double mag2() { return x * x + y * y; }

  P nor() { return * this * ( 1.0 / mag() ); }

  P rot() { return P( -y, x ); }
  P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
  P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

#define N 44444

P C[N];
double R[N];
int n, wsh[N];
double curY;

struct E {
  int cid;
  bool open;

  E() {}
  E( int cid, bool open ): cid(cid), open(open) {}

  double getX( double now ) const {
    P c = C[cid]; 
    double r = R[cid];
    if ( SQR( r ) < SQR( now - c.y ) - EPS ) while ( 1 );
    double t = sqrt( SQR(r) - SQR(now - c.y) + EPS );
    double x = open ? c.x - t : c.x + t;
    return x;
  }

  bool operator<( const E &e ) const {
    double x1 = getX( curY ), x2 = e.getX( curY );
    if ( !feq(x1, x2) ) return x1 < x2;
    if ( cid == e.cid ) return open > e.open;
    while ( 1 );
  }
};

bool comp_evt( const int &a, const int &b ) {
  double ya, yb;
  ya = a > 0 ? C[a].y + R[a] : C[-a].y - R[-a];
  yb = b > 0 ? C[b].y + R[b] : C[-b].y - R[-b];

  if ( !feq( ya, yb ) ) return ya > yb;
  return a > b;
}

typedef set<E>::iterator SIT;

void sweep() {
  set<E> T;
  int q[N * 2], m = 0;
  FOE( i, 1, n ) {
    q[m++] = i;
    q[m++] = -i;
  }
  CLR( wsh, 0 );
  sort( q, q + m, comp_evt );
  T.clear();
  REP( i, m ) {
    if ( q[i] > 0 ) {
      int v = q[i], ok = 0;
      E e1 = E( v, 1 ), e2 = E( v, 0 );
      curY = C[v].y + R[v];

      SIT pit = T.lower_bound( e1 );

      if ( pit == T.end() || pit->open ) {
        wsh[v] = 1;
        T.insert( e1 );
        T.insert( e2 ); 
      }

    } else if ( q[i] < 0 ) {
      int v = -q[i];
      E e1 = E( v, 1 ), e2 = E( v, 0 );
//      curY = C[v].y - R[v];

      if ( wsh[v] ) {
        T.erase( e1 ); 
        T.erase( e2 );
      }
    } 
  }
}

int main() {
  scanf( "%d", &n );
  FOE( i, 1, n ) {
    scanf( "%lf", &R[i] );
    C[i].eat(); 
  }

  sweep();
  
  int cnt = 0, fl = 0;

  FOE( i, 1, n ) if ( wsh[i] ) cnt++;
  printf( "%d\n", cnt );
  FOE( i, 1, n ) if ( wsh[i] ) printf( "%d%s", i, --cnt ? " " : "\n" );

  return 0;
}

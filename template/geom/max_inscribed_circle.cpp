#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

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
	void out() { printf( "(%f, %f)", x, y ); }

	P operator+( P p ) { return P( x + p.x, y + p.y ); }
	P operator-( P p ) { return P( x - p.x, y - p.y ); }
	P operator*( double s ) { return P( x * s, y * s ); }
	double operator*( P p ) { return x * p.x + y * p.y; }
	double operator^( P p ) { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return feq( x, p.x ) && feq( y, p.y ); }

	double mag() { return sqrt( x * x + y * y ); }
	double mag2() { return x * x + y * y; }

	P nor() { return * this * ( 1.0 / mag() ); }

	P rot() { return P( -y, x ); }
  P rrot() { return P( y, -x); }
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

bool btw( P a, P b, P c ) {
	return feq( ( b - a ).mag() + ( c - b ).mag(), ( a - c ).mag() );
}

bool lli( P a, P b, P c, P d, P &res ) {
	if( feq( ( b - a ) ^ ( d - c ), 0.0 ) ) return false;
	res = a + ( b - a ) * ( area( c, d, a )  / ( area( c, d, a ) - area(c, d, b) ) );
	return true;
}

bool up( P a ) {
  return a.y == 0.0 ? a.x > 0.0 : a.y > 0;
}

/**
  * O(nlogn) half plane intersection
  * zzy's method
  *   sweep one round, no merge convex hull
  **/

#define N 11111

P hp[N][2], res[N];
int hn, rn;

bool comp( const int &a, const int &b ) {
  P pa = hp[a][1] - hp[a][0], pb = hp[b][1] - hp[b][0];
  if ( up(pa) ^ up(pb) ) return up(pa);
  if ( feq(pa ^ pb, 0.0) ) return ccw( hp[b][0], hp[b][1], hp[a][0]);
  return ccw( P(0.0, 0.0), pa, pb);
}

void hpi() {
  int A[N], q[N], qh, qt;
  P u[N], t;

  qh = qt = 0;
  REP(i, hn) A[i] = i;
  sort(A, A + hn, comp);

  REP(i, hn) {
    if ( qt == 0 ) {
      q[qt++] = A[i];
    } else {
      P ai = hp[A[i]][1] - hp[A[i]][0], ql = hp[q[qt-1]][1] - hp[q[qt-1]][0];
      if ( feq( ai ^ ql, 0.0 ) && ai * ql > EPS ) continue;
      while( qt - qh >= 2 && !Ccw( hp[A[i]][0], hp[A[i]][1], u[qt-2]) ) qt--;
      q[qt++] = A[i];
      lli(hp[q[qt-2]][0], hp[q[qt-2]][1], hp[q[qt-1]][0], hp[q[qt-1]][1], u[qt-2]); 
    }
  }

  bool f = 1;
  while( f ) {
    f = 0;
    while( qt - qh >= 2 && !Ccw( hp[q[qh]][0], hp[q[qh]][1], u[qt-2]) ) f = 1, qt--;
    while( qt - qh >= 2 && !Ccw( hp[q[qt-1]][0], hp[q[qt-1]][1], u[qh]) ) f = 1, qh++;
  }

  rn = 0;
  int k = qt - qh;
  REP(i, k) {
    lli( hp[q[qh+i]][1], hp[q[qh+i]][0], hp[q[qh+(i+1)%k]][1], hp[q[qh+(i+1)%k]][0], t);
    res[rn++] = t;
  }
}

void shrink( P p[], int n, double r, P ans[], int &sn ) {
  // assume ccw
  REP( i, n ) {
    P nr = p[(i + 1) % n] - p[i];
    nr = nr.rot().nor() * r;
    hp[i][0] = p[i] + nr;
    hp[i][1] = p[(i + 1) % n] + nr;
  }
  hn = n;
  hpi();
  copy( res, res + rn, ans );
  sn = rn;
}

int n, sn;
P p[111], pp[111];
double hi, lo;

int main() {
  while ( scanf( "%d", &n ), n ) {
    REP( i, n ) p[i].eat();
    hi = 10000.0, lo = 0;

    while ( hi > lo + 1e-7 ) {
      double mi = ( hi + lo ) / 2.0;
      shrink( p, n, mi, pp, sn ); 
      if ( sn <= 2 ) hi = mi;
      else lo = mi;
    }
    printf( "%.6f\n", lo );
  }
	return 0;
}

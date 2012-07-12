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

#define INF 1e12
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
	void out() { printf( "%f, %f ", x, y ); }

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
	res = a + ( b - a ) * ( area( c, d, a )  / ( area( c, d, a ) - area(c, d, b) ) );
	return true;
}

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

double parea( P p[], int n ) {
  if( n < 3 ) return 0.0;
  double ret = 0.0;
  REP(i, n) ret += area( P(0.0, 0.0), p[i], p[(i + 1) % n]);
  return fabs( ret );
}

/**
  * O(nlogn) half plane intersection
  * zzy's method
  *   sweep one round, no merge convex hull
  **/

#define N 111111

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

P ln[N][2];
int n;

int main() {
  int cas;
  scanf( "%d", &cas );
  while (cas--) {
//    puts( "-------------------------------------");
    double xl, xr, yt = -INF, yb = INF;
    double ta, ba;
    P ll[2], rl[2];
    scanf( "%d", &n );
    int cnt = 0;
    REP(i, n) {
      ln[cnt][0].eat();
      ln[cnt][1].eat();
      if( !feq(ln[cnt][0].x, ln[cnt][1].x) ) cnt++;
    }
    scanf( "%lf%lf", &xl, &xr );

    if ( fge( xl, xr ) ) {
      printf( "%f\n", 0.0 );
      continue;
    }

    n = cnt;
    if ( n == 0 ) while( 1 );

    ll[0] = P( xl, 0.0 );
    ll[1] = P( xl, 1.0 );

    rl[0] = P( xr, 0.0 );
    rl[1] = P( xr, 1.0 );

    // upper part
//    puts( "upper: " );
    REP(i, n) {
      if( ln[i][0].x > ln[i][1].x) swap(ln[i][0], ln[i][1]);
      hp[i][0] = ln[i][0];
      hp[i][1] = ln[i][1];
      P t1, t2;
      if ( !lli(hp[i][0], hp[i][1], ll[0], ll[1], t1) ) while( 1 );
      if ( !lli(hp[i][0], hp[i][1], rl[0], rl[1], t2) ) while( 1 );
      yt = max(yt, max(t2.y, t1.y));
      yb = min(yb, min(t1.y, t2.y));
    }

    yt += 1.0;
    yb -= 1.0;

    hn = n + 4;
    hp[n][0] = P( xr, yt );
    hp[n][1] = P( xl, yt );
    hp[n+1][0] = P( xl, yb );
    hp[n+1][1] = P( xr, yb );
    hp[n+2][0] = rl[0];
    hp[n+2][1] = rl[1];
    hp[n+3][0] = ll[1];
    hp[n+3][1] = ll[0];
    hpi();
    ta = parea( res, rn );

    // lower part
//    puts( "lower: " );
    REP(i, n) 
      swap(hp[i][0], hp[i][1]);

    hpi();
    ba = parea( res, rn );

    double ans = ( yt - yb ) * ( xr - xl ) - ta - ba;
    if ( ans < 0.0 ) while ( 1 );
    printf( "%f\n", ans );
//    puts( "-------------------------------------");
  }

	return 0;
}

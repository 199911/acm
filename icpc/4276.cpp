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

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

bool down( P a, P b, P c ) {
  return fle( a.x, c.x ) && flt( c.x, b.x ) && ccw( b, a, c );
}

#define N 111

P R[N], B[N], G[N];
int rn, bn, gn;

int gc[N][N], rc[N][N];

int count_red( int i, int j, int k ) {
  return abs( rc[i][j] + rc[j][k] - rc[i][k] );
}

int count_green( int i, int j, int k ) {
  return abs( gc[i][j] + gc[j][k] - gc[i][k] );
}

int main() {
  int cas = 1;
  while ( scanf( "%d%d%d", &rn, &gn, &bn ), rn >= 0 && bn >= 0 && gn >= 0 ) {
    REP( i, rn ) R[i].eat();
    REP( i, gn ) G[i].eat();
    REP( i, bn ) B[i].eat();

    sort( R, R + rn );
    sort( G, G + gn );
    sort( B, B + bn );

    // precompute
    REP( i, bn ) FOR( j, i + 1, bn ) {
      rc[i][j] = 0;
      gc[i][j] = 0;

      REP( k, gn ) {
        if ( down( B[i], B[j], G[k] ) ) gc[i][j]++;
      }
      REP( k, rn ) {
        if ( down( B[i], B[j], R[k] ) ) rc[i][j]++;
      }
    }

    int rb = 0, gb = 0;

    REP( i, bn ) FOR( j, i + 1, bn ) FOR( k, j + 1, bn ) {
      int cr = count_red( i, j, k );
      int cg = count_green( i, j, k );
      if ( cr > cg ) rb++;
      else if ( cg > cr ) gb++;
    }

    printf( "Case %d: %d %d\n", cas++, rb, gb );

  }
	return 0;
}

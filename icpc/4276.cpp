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
	if ( a.x > b.x ) swap( a, b );
	return ( fle( a.x, c.x ) && fle( c.x, b.x ) && ccw( b, a, c) );
}

bool Down( P a, P b, P c ) {
	if ( a.x > b.x ) swap( a, b );
	return ( fle( a.x, c.x ) && fle( c.x, b.x ) && Ccw( b, a, c) );
}

P r[111], g[111], b[111];
int rn, gn, bn, gc[111][111], rc[111][111], Gc[111][111], Rc[111][111];

void precompute() {
	REP( i, bn ) FOR( j, i + 1, bn ) {
		gc[i][j] = gc[j][i] = 0;
		rc[i][j] = rc[j][i] = 0;
		Gc[i][j] = Gc[j][i] = 0;
		Rc[i][j] = Rc[j][i] = 0;
		REP( k, gn ) { 
			if ( down( b[i], b[j], g[k] ) ) gc[i][j]++, gc[j][i]++;
			if ( Down( b[i], b[j], g[k] ) ) Gc[i][j]++, Gc[j][i]++;
		}
		if ( gc[i][j] != Gc[i][j] ) while ( 1 );
		REP( k, rn ) {
			if ( down( b[i], b[j], r[k] ) ) rc[i][j]++, rc[j][i]++;
			if ( Down( b[i], b[j], r[k] ) ) Rc[i][j]++, Rc[j][i]++;
		}
		if ( Rc[i][j] != rc[i][j] ) while ( 1 );
	}
}

int cntr( int i, int j, int k ) {
	if ( b[i].x > b[j].x ) swap(i, j);
	if ( b[i].x > b[k].x ) swap(i, k);
	if ( b[j].x > b[k].x ) swap(j, k);

	if ( down( b[i], b[j], b[k] ) ) return rc[i][k] - Rc[i][j] - Rc[j][k];
	else return rc[i][j] + rc[j][k] - Rc[i][k]; 
}

int cntg( int i, int j, int k ) {
	if ( b[i].x > b[j].x ) swap(i, j);
	if ( b[i].x > b[k].x ) swap(i, k);
	if ( b[j].x > b[k].x ) swap(j, k);


	if ( down( b[i], b[j], b[k] ) ) return rc[i][k] - Gc[i][j] - Gc[j][k];
	else return gc[i][j] + Gc[j][k] - Gc[i][k]; 
}

int main() {

	int cas = 0;

	while ( scanf( "%d%d%d", &rn, &gn, &bn ), rn >= 0 ) {
		REP( i, rn ) r[i].eat();
		REP( i, gn ) g[i].eat();
		REP( i, bn ) b[i].eat();

		precompute();

		int rb = 0, gb = 0;

		REP( i, bn ) 
			FOR( j, i + 1, bn ) 
				FOR( k, j + 1, bn ) {
					int s = cntr( i, j, k ), t = cntg( i, j, k );
					if ( s > t ) rb++;
					else if ( t > s ) gb++;
				}

		printf( "Case %d: %d %d\n", ++cas, rb, gb );
	}
	return 0;
}

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
#include <map>
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

const double PI = 4.0 * atan( 1.0 );

struct P {
	double x, y;
	P() {}
	P( double x, double y ): x(x), y(y) {}
	void eat() { scanf( "%lf%lf", &x, &y ); }
	void out() const  { printf( "(%f, %f)", x, y ); }

	P operator+( const P p ) const { return P( x + p.x, y + p.y ); }
	P operator-( const P p ) const { return P( x - p.x, y - p.y ); }
	P operator*( const double s ) const { return P( x * s, y * s ); }
	double operator*( const P p ) const { return x * p.x + y * p.y; }
	double operator^( const P p ) const { return x * p.y - y * p.x; }
	bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
	bool operator==( const P p ) const { return feq( x, p.x ) && feq( y, p.y ); }

	double mag() { return sqrt( x * x + y * y ); }
	double mag2() { return x * x + y * y; }

	P nor() { return * this * ( 1.0 / mag() ); }

	P rot() { return P( -y, x ); }
	P rrot() { return P( y, -x ); }
	P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
	P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

void pbisect( P a, P b, P &c, P &d ) {
	c = ( a + b ) * 0.5;
	d = c + ( b - a ).rot();
}

bool lli( P a, P b, P c, P d, P &res ) {
	if ( fabs( ( b - a ) ^ ( c - a ) ) < EPS ) 
		return false;
	double s = ( ( c - a ) ^ ( d - c ) ) / ( ( b - a ) ^ ( d - c ) );
	res = a + ( b - a ) * s;
	return true;
}

void ball( P a, P b, P &c, double &R ) {
	c = ( a + b ) * 0.5;
	R = ( a - b ).mag() * 0.5;
}

bool ball( P a, P b, P c, P &ctr, double &r ) {
	if ( fabs( ( b - a ) ^ ( c - a ) ) < EPS )
		return false;
	P s, t, u, v;
	pbisect( a, b, s, t );
	pbisect( b, c, u, v );
	lli( s, t, u, v, ctr );
	r = ( ctr - a ).mag();
	return true;
}

void MinEnclosingBall( P p[], int n, int a, int b, int c, P &ctr, double &r ) {
	if ( n == 0 ) {
		if ( b == -1 ) { ctr = p[a]; r = EPS; }
		else if ( c == -1 ) { ball( p[a], p[b], ctr, r ); }
		else { ball( p[a], p[b], p[c], ctr, r ); }
	} else {
		MinEnclosingBall( p, n - 1, a, b, c, ctr, r );
		if ( ( p[n - 1] - ctr ).mag() > r + EPS ) {
			if ( a == -1 ) a = n - 1;
			else if ( b == -1 ) b = n - 1;
			else if ( c == -1 ) c = n - 1;
			else puts( "oops" );
			MinEnclosingBall( p, n - 1, a, b, c, ctr, r );
		}
	}
}

void MinEnclosingBall( P p[], int n, P &ctr, double &r ) {
	random_shuffle( p, p + n );
	MinEnclosingBall( p, n, -1, -1, -1, ctr, r );
}

#define N 22222

double r, R;
int n;
P p[N], ctr;

int main() {
	while( scanf( "%d", &n ), n ) {
		for( int i = 0; i < n; i++ ) 
			p[i].eat();
		scanf( "%lf", &R );
		MinEnclosingBall( p, n, ctr, r );
		if ( R > r - EPS ) puts( "The polygon can be packed in the circle." );
		else puts( "There is no way of packing that polygon." );
	}
	return 0;
}

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
	if ( !feq( ( b - a ) ^ ( c - a ), 0.0 ) ) return 0;
	double s = ( b - a ) * ( c - a );
	return fge( s, 0.0 ) && fle( s, ( c - a ).mag2() );
}

// assume p is convex given in ccw order
void hull( P p[], int n, P h[], int &hn ) {
	hn = 0;
	sort( p, p + n );

	for( int i = 0; i < n; i++ ) {
		while ( hn >= 2 && !Ccw( h[hn - 2], h[hn - 1], p[i] ) ) hn--;
		h[hn++] = p[i];
	}

	for( int i = n - 1, s = hn; i > 0; i-- ) {
		while ( hn > s && !Ccw( h[hn - 2], h[hn - 1], p[i] ) ) hn--;
		h[hn++] = p[i];
	}
}

double ConvexPolyDiameter( P p[], int n, P &a, P &b ) {
	double ret = 0.0;
	if ( n == 1 ) { a = b = p[0]; return 0.0; }
	if ( n == 2 ) { a = p[0]; b = p[1]; return ( b - a ).mag(); }

	for( int i = 0, j = 0; i < n; i++ ) {
		if ( ret < ( p[i] - p[j] ).mag2() ) {
			ret = ( p[i] - p[j] ).mag2();
			a = p[i]; b = p[j];
		}
		double cur = ( p[(i + 1) % n] - p[i] ) ^ ( p[j] - p[i] ), last = cur;
		while (  j < n && ( cur = ( p[( i + 1 ) % n] - p[i] ) ^ ( p[(j + 1 ) % n] - p[i] ) ) > last + EPS  ){
			j = ( j + 1 ) % n;
			if ( ret < ( p[i] - p[j] ).mag2() ) {
				a = p[i]; b = p[j];
				ret = ( p[i] - p[j] ).mag2();
			}
		}
	}
	
	return sqrt( ret );
}

#define N 222222

double FarthestPair( P p[], int n, P &a, P &b ) {
	P h[N];
	int hn;
	hull( p, n, h, hn );
	return ConvexPolyDiameter( h, hn, a, b );
}

int main() {
	P p[N], a, b;
	int n;
	scanf( "%d", &n );
	REP( i, n ) p[i].eat();
	double ret = FarthestPair( p, n, a, b );
	printf( "%f\n", ret );
	return 0;
}

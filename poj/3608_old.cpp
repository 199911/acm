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
#define INF 1e10
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

bool lli( P a, P b, P c, P d, double &s, double &t, P &res ) {
	if ( fabs( (b - a) ^ (d - c)) < EPS ) {
		return false;
	} else {
		s = area( c, d, a ) / ( area(c, d, a ) - area(c, d, b) );
		t = area( a, b, c ) / ( area(a, b, c) - area(a, b, d) );
		res = a + ( b - a ) * s;
		return true;
	}	
}

bool ssi( P a, P b, P c, P d, P &res) {
	double s, t;
	if ( lli( a, b, c, d, s, t, res ) ) {
		if ( fge(s, 0.0) && fle(s, 1.0 ) && fge(t, 0.0) && fle(t, 1.0) ) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

double psd( P a, P b, P c ) {
	if ( ( c - a ) * ( b - a ) > EPS && ( a - b ) * ( c - b ) > EPS ) {
		return 2.0 * fabs( area(a, b, c) / (b - a).mag());
	} else {
		return min((b - c).mag(), (a - c).mag());
	}
}

double ssd( P a, P b, P c, P d ) {
	P asd;
	if ( ssi(a, b, c, d, asd ) ) {
		return 0.0;
	} else {
		return min( min(psd(a, b, c), psd(a, b, c)), min(psd(c, d, a), psd(c, d, b)));
	}
}

// compute the minimum distance of two disjoint convex polygon
// assume all vertices are given in counter clockwize order
double ppd1(P p1[], int n1, P p2[], int n2) {
	double maxY = -INF, minY = INF;
	int maxi, mini;
	REP(i, n1) 
		if ( p1[i].y > maxY) {
			maxY = p1[i].y;
			maxi = i;
		}
	REP(i, n2) 
		if( p2[i].y < minY) {
			minY = p2[i].y;
			mini = i;
		}

	double mind = INF;
	for(int j = mini, i = maxi; i < maxi + n1; i++) {
		double last = -INF;
		int up = 0;
		while( j < mini + n2 * 2 ) {
			double cur = area( p1[i%n1], p1[(i+1)%n1], p2[j%n2]);
			if ( cur < last -EPS ) break;
			mind = min( psd( p1[i%n1], p1[(i+1)%n1], p2[j%n2]), mind );
			last = cur;
			j++; up = 1;
		}
		if( up ) j--;
	}

	return mind;
}

double ppd( P p1[], int n1, P p2[], int n2) {
	return min( ppd1(p1, n1, p2, n2), ppd1(p2, n2, p1, n2));
}

#define N 22222

int n1, n2;
P p1[N], p2[N];

int main() {

	while( scanf( "%d%d", &n1, &n2 ), n1 || n2 ) {
		REP(i, n1) p1[i].eat();
		REP(i, n2) p2[i].eat();

		REP(i, n1) {
			if( !ccw(p1[i], p1[(i+1)%n1], p1[(i+2)%n1]) ) {
				reverse(p1, p1 + n1);
				break;
			}
		}

		REP(i, n2) {
			if( !ccw(p2[i], p2[(i+1)%n2], p2[(i+2)%n2]) ) {
				reverse(p2, p2 + n2);
				break;
			}
		}

		printf("%f\n", ppd(p1, n1, p2, n2));
	}

	return 0;
}

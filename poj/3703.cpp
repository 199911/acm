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

const double PI = atan( 1.0 ) * 4;

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

double r;

P left( P a ) {
	double len = sqrt( a.mag2() - r * r );
	double si = r / a.mag(), co = len / a.mag();
	P ret = ( a.nor() * len ).rot( si, co );

	return ret;
}

P right( P a ) {
	double len = sqrt( a.mag2() - r * r );
	double si = -r / a.mag(), co = len / a.mag();
	P ret = ( a.nor() * len ).rot( si, co );
	return ret;
}

double ang( P a ) {
	double ans = atan2( a.y, a.x );
	if ( ans < -EPS ) ans += 2 * PI;
	return ans;
}

void exp( P a, P b, P &c, P &d ) {
	if ( Ccw( P(0.0, 0.0), a, b ) ){
		c = right( a );
		d = left( b );
	} else {
		c = left( a );
		d = right( b );
		swap( c, d );
	}
}

typedef pair<double, double> PDD;

#define N 5555
PDD I[N];
int m;


int main() {
	int n; 
	m = 0;
	scanf( "%d%lf", &n, &r );
	REP( i, n ) {
		int k; 
		P p[55];
		scanf( "%d", &k );
		REP( j, k ) p[j].eat();
		REP( j, k ) {
			P a, b, c, d;
			double s, t;
			a = p[j];
			b = p[(j + 1) % k];
			exp( a, b, c, d );
			s = ang(c);
			t = ang(d);
			if ( t < s ) t += 2 * PI;
			I[m++] = PDD(s, t);
		}
	}

	sort( I, I + m );

	double cur = 0.0, le = 0.0;
	int ok = 1;

	REP( i, m ) {
		double st = I[i].first, en = I[i].second;
		if ( st > cur + EPS ) { le = st; ok = 0; }
		cur = en;
		if ( ok || en > 2 * PI - EPS && en - 2 * PI > le ) ok = 1;
	}

	printf("%s\n", !ok ? "Survive!" : "Baffling!" ); 

	return 0;
}

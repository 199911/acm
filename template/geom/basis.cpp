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
  bool operator<( const P &p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P &p ) const { return feq( x, p.x ) && feq( y, p.y ); }

	double mag() { return sqrt( x * x + y * y ); }
	double mag2() { return x * x + y * y; }

	P nor() { return * this * ( 1.0 / mag() ); }

	P rot() { return P( -y, x ); }
	P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
	P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};


// signed area of triangle
double area(P a, P b, P c) {
	return 0.5 * ( ( b - a ) ^ ( c - a ) );
}

// turn left
bool ccw( P a, P b, P c ) {
  return fge( area( a, b, c ), 0.0 );
}

// turn strictly left
bool Ccw( P a, P b, P c ) {
  return fgt( area( a, b, c ), 0.0 );
}

// line line intersection
bool lli( P a, P b, P c, P d, P &res ) {
	if( feq( ( b - a ) ^ ( d - c ), 0.0 ) ) return false;
	res = a + ( b - a ) * ( area( c, d, a )  / ( area( c, d, a ) - area(c, d, b) ) );
	return true;
}

// segment segment intersection
bool ssi(P a, P b, P c, P d, P &res) {
  if( ! lli(a, b, c, d, res) ) return false;
  else 
    if( btw(a, res, b) && btw(c, res, d) ) 
      return true; else return false;
}

bool btw( P a, P b, P c ) {
  if ( fabs((b - a)^(c - a)) > EPS ) return false;
  return (b - a)*(c - a) > -EPS && (b - a)*(c - a)<(c - a).mag2() + EPS
}

double parea( P p[], int n ) {
  double ret = 0;
  for( int i = 0; i < n; i++ ) 
    ret += p[i]^p[(i + 1)%n];
  return 0.5* fabs( ret );
}

bool up( P a ) { return a.y == 0 ? a.x > 0: a.y > 0; }

int inpoly( P p[], int n, P a ) {
  int ans = 0;
  for( int i = 0; i < n; i++ ) 
    if (up(p[i] - a) ^ up(p[(i+1)%n] - a) )
      ans += ccw( a, p[i], p[(i + 1) % n]) ? 1 : -1;
  return ans;
}

int inpoly( P p[], int n, P a ) {
  double ang = 0;
  for( int i = 0; i < n; i++ ) {
    P s = p[i] - a, t = p[( i + 1 ) % n] - a;
    ang += atan2( s ^ t, s * t );
  }
  return fabs( ang ) > 1;
}


int main() {
	return 0;
}

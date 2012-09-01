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

double ang( P a ) {
  double ret = atan2( a.y, a.x );
  if ( ret < -EPS ) ret += 2 * PI;
  return ret;
}

double R, r, s, o, vp, v, t, Q;
P cur, st;

double spd( P a, P b, P c ) {
  double t = (c - a) * (b - a);
  if ( b == c ) return ( b - a ).mag();
  if ( t > 0 && t < (b - a).mag2() ) {
    return fabs( (b - a).nor() ^ (c - a) );
  } else {
    return min( (c - b).mag(), (c - a).mag() );
  }
}

double dist( P a, P b ) {
  double d = spd( a, b, P(0, 0) );
//  printf("---- %lf ----", d);
  if ( d > r - EPS ) {
    return (b - a).mag();
  } else { 
    double th = atan2( a.y, a.x ) - atan2( b.y, b.x ); 
    while ( th < -EPS ) th += 2 * PI;
    while ( th > 2 * PI + EPS ) th -= PI;

    if ( th > PI ) th = 2 * PI - th;

    double al = acos( r / a.mag() ); 
    double bt = acos( r / b.mag() );

    double len = ( th - al - bt ) * r;
    double l1 = sqrt( b.mag2() - r * r + EPS );
    double l2 = sqrt( a.mag2() - r * r + EPS );

    return len + l1 + l2;
  }
}


int main() {
  st.eat();
  scanf( "%lf", &vp );
  cur.eat();
  scanf( "%lf%lf", &v, &r );
  R = st.mag();
  o = vp / R;
  s = ang( st );
  t = ang( cur );

  Q = t - s;
  while ( Q < -EPS ) Q += 2 * PI;

  double up = 1e9, lo = 0;

  while ( up > lo + 1e-10 ) {
    double mid = (up + lo) / 2.0;

    double ang = s + o * mid;

    P p = P( R * cos(ang), R * sin(ang) );

    double d = dist( p, cur );

    if ( d < mid * v + EPS ) {
      up = mid;
    } else {
      lo = mid;
    }
  }

  printf( "%.9f\n", up);

	return 0;
}

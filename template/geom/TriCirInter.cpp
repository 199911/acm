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

bool lci( P a, P b, P c, double r, double &s, double &t ) {
  double A = ( b - a ).mag2(), B = 2.0 * (( a - c ) * ( b - a )), C = ( a - c ).mag2() - r * r;
  double det = B * B - 4.0 * A * C;
  if ( det < -EPS ) return false;
  det = sqrt( det + EPS );
  s = ( -B - det ) / ( 2.0 * A );
  t = ( -B + det ) / ( 2.0 * A );
  return true;
}

double arc( P a, P b, double r ) {
  double th = atan2( b.y, b.x ) - atan2( a.y, a.x );
  if ( th < 0 ) th += 2.0 * PI;
  if ( th > PI ) th = 2.0 * PI - th;
  return r * r * th * 0.5;
}

#define btw(a,b,c) (((b)>(a)-EPS)&&((b)<(c)+EPS))

// assume orgin is the center of circle and one of the triangle vertices
double TriCirIntersect( P a, P b, double r ) {
  double s, t;
  if ( !lci( a, b, P( 0.0, 0.0 ), r, s, t ) ) {
    return arc( a, b, r );
  } else {
    if ( !btw( 0.0, s, 1.0 ) && !btw( 0.0, t, 1.0 ) ) {
      if ( a.mag2() < r * r ) return 0.5 * fabs( a ^ b );
      else return arc( a, b, r );
    } else if ( btw( 0.0, s, 1.0 ) && btw( 0.0, t, 1.0 ) ) {
      P c = a + ( b - a ) * s, d = a + ( b - a ) * t;
      return arc( a, c, r ) + 0.5 * fabs( c ^ d ) + arc( d, b, r );
    } else {
      P c = a + ( b - a ) * ( btw( 0.0, s, 1.0 ) ? s : t );
      double ret = 0.0;
      if ( a.mag2() < r * r ) ret += 0.5 * fabs( a ^ c );
      else ret += arc( a, c, r );
      if ( b.mag2() < r * r ) ret += 0.5 * fabs( b ^ c );
      else ret += arc( b, c, r );

      return ret;
    }
  }
}

int main() {
  P p[3], c;
  double r, ans;
  while ( 1 ) {
    REP( i, 3 ) p[i].eat();
    c.eat();
    REP( i, 3 ) p[i] = p[i] - c;
    if ( scanf( "%lf", &r ) == EOF ) break;
    ans = 0.0;
    REP( i, 3 ) {
      double tmp = TriCirIntersect( p[i], p[(i + 1) % 3], r );
      if ( (p[i] ^ p[(i + 1) % 3]) < -EPS ) ans -= tmp;
      else ans += tmp;
    }
    ans = fabs( ans );
    printf( "%.2f\n", ans );
  }
  return 0;
}

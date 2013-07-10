#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define LL long long

#define EPS 1e-9

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

  double mag() { return sqrt( x * x + y * y ); }
  double mag2() { return x * x + y * y; }

  P nor() { return * this * ( 1.0 / mag() ); }
};

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
  P p[55], c;
  int n;
  double r, ans;
  while ( scanf( "%d%lf", &n, &r ) != EOF ) {
    REP( i, n ) p[i].eat();
    ans = 0.0;
    REP( i, n ) {
      double tmp = TriCirIntersect( p[i], p[(i + 1) % n], r );
      if ( (p[i] ^ p[(i + 1) % n]) < -EPS ) ans -= tmp;
      else ans += tmp;
    }
    ans = fabs( ans );
    printf( "%f\n", ans );
  }
  return 0;
}

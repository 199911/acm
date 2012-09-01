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

bool cli( P a, P b, P c, double r, P &r1, P &r2 ) {
  double A = (b - a).mag2(), B = (a - c) * (b - a) * 2.0, C = (a - c).mag2() - r * r;
  double det = B * B - 4.0 * A * C;
  if ( det > -EPS ) {
    double rt = sqrt( det + EPS );
    double t1 = ( -B + rt ) / (2.0 * A);
    double t2 = ( -B - rt ) / (2.0 * A);
    r1 = a + (b - a) * t1;
    r2 = a + (b - a) * t2;
    return true;
  }
  return false;
}

bool cci( P a, double ra, P b, double rb, P &r1, P &r2 ) {
  if ( (a - b).mag2() < SQR( ra - rb ) - EPS || (a - b).mag2() > SQR(ra + rb) + EPS ) return false;
  if ( ra < rb ) {
    swap( ra, rb );
    swap( a, b );
  }

  double cs = (ra * ra + rb * rb - (a - b).mag2()) / (2.0 * ra * rb), si = sqrt( 1.0 - cs * cs + EPS );
  double h = ra * rb * si / (b - a).mag();
  double la = sqrt( ra * ra - h * h );

  r1 = a + (b - a).nor() * la + (b - a).nor().rot() * h;
  r2 = a + (b - a).nor() * la + (b - a).nor().rrot() * h;

  return true;
}

double lli( P a, P b, P c, P d, P &res ) {
  if ( feq( (b - a) ^ (d - c), 0.0) ) return false;
  double s = ((c - a) ^ (d - c)) / ((b - a) ^ (d - c));
  double t = ((a - c) ^ (b - a)) / ((d - c) ^ (b - a));
  
  res = a + (b - a) * s;

  return true;
}

int main() {
  P a, b, c;
  double ra, rb, rc;

  a.eat(); scanf( "%lf", &ra );
  b.eat(); scanf( "%lf", &rb );
  c.eat(); scanf( "%lf", &rc );

  if ( feq( ra, rb ) && feq( rb, rc ) ) {
    P s, t, u, v, r;
    s = (a + b) * 0.5;
    t = s + (b - a).nor().rot();
    u = (b + c) * 0.5;
    v = u + (c - b).nor().rot();

    if( lli(s, t, u, v, r) ) {
      printf( "%.5f %.5f\n", r.x + EPS, r.y + EPS );
    }
  } else if ( feq( ra, rb ) || feq( rb, rc ) ) {
    if ( feq( rb, rc ) ) { 
      swap( rc, ra );
      swap( a, c );
    }
    P s, t, w;
    s = (a + b) * 0.5;
    t = s + (b - a).nor().rot();

    double C = rc / rb;
    P ctr = (b * (C * C) - c) * (1.0 / (C * C - 1) );
    w = c + (b - c) * ( rc / (rc + rb));

    double R = (ctr - w).mag();

//    ctr.out();
//    printf( "%f\n",  R); 
//    puts( "" );

    P r1, r2;

    if ( cli( s, t, ctr, R, r1, r2 ) ) {
      if ( (r1 - a).mag2() < (r2 - a).mag2() ) {
        printf( "%.5f %.5f\n", r1.x + EPS, r1.y + EPS );
//        printf( "%f %f %f\n", (r1 - a).mag(), (r1 - b).mag(), (r1 - c).mag());
      } else {
        printf( "%.5f %.5f\n", r2.x + EPS, r2.y + EPS);
//        printf( "%f %f %f\n", (r2 - a).mag(), (r2 - b).mag(), (r2 - c).mag());
      }
    }
  } else {
    P s, t, w;
    double rs, rt;

    double C = ra / rb;
    s = (b * (C * C) - a) * (1.0 / (C * C - 1));
    w = a + (b - a) * ( ra / (ra + rb));
    rs = (s - w).mag();

    C = rc / rb;
    t = (b * (C * C) - c ) * (1.0 / (C * C - 1));
    w = c + (b - c) * (rc / (rc + rb));
    rt = (t - w).mag();

    P r1, r2;
    if ( cci( s, rs, t, rt, r1, r2 ) ) {
      if ( (r1 - a).mag2() < (r2 - a).mag2() ) {
        printf( "%.5f %.5f\n", r1.x + EPS, r1.y + EPS );
//        printf( "%f %f %f\n", (r1 - a).mag(), (r1 - b).mag(), (r1 - c).mag());
      } else {
        printf( "%.5f %.5f\n", r2.x + EPS, r2.y + EPS );
//        printf( "%f %f %f\n", (r2 - a).mag(), (r2 - b).mag(), (r2 - c).mag());
      }
    }
  }
	return 0;
}

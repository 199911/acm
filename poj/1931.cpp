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
  bool operator==( const P p ) const { return feq(x, p.x) && feq(y, p.y); }

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

double angle(P a, P b) {
  return atan2(b.y, b.x) - atan2(a.y, a.x);
}

bool lli( P a, P b, P c, P d, P &res ) {
	if( feq( ( b - a ) ^ ( d - c ), 0.0 ) ) return false;
	res = a + ( b - a ) * ( area( c, d, a )  / ( area( c, d, a ) - area(c, d, b) ) );
	return true;
}

bool btw( P a, P b, P c ) {
	return feq( ( b - a ).mag() + ( c - b ).mag(), ( a - c ).mag() );
}

bool ssi(P a, P b, P c, P d, P &res) {
  if( ! lli(a, b, c, d, res) ) {
    return false;
  } else {
    if( btw(a, res, b) && btw(c, res, d) ) {
      return true;
    } else {
      return false;
    }
  }
}


int main() {
  int n; 
  double agl, sc;
  P p1[12], p2[12], t1, t2;
  while( scanf("%d", &n), n ) {
    REP(i, n) p1[i].eat();
    REP(i, n) p2[i].eat();

    int done = 0;

    REP(i, n) {
      REP(j, n) {
        sc = ( p2[j] - p2[(j + 1) % n] ).mag() / ( p1[i] - p1[(i + 1) % n]).mag();
        agl = angle( p1[( i + 1 ) % n] - p1[i], p2[( j + 1 ) % n] - p2[j] );
        t1 = p1[i]; t2 = p2[j];

        REP(k, n) {
          p1[k] = p1[k] - t1;
          p2[k] = p2[k] - t2;
        }

        REP(k, n) {
          p1[k] = p1[k] * sc;
        }

        REP(k, n) {
          p1[k] = p1[k].rot(agl);
        }

        int ok = 1;
        REP(k, n) {
          if ( !( p1[k] == p2[k] ) ) ok = 0;
        }
        if ( ok ) done = 1;
      }
    }

    printf("%s\n", done ? "similar" : "dissimilar");

  }
	return 0;
}

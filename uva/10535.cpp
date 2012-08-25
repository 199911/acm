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

#define PDI pair<double,int>

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
  if ( ret < -EPS ) ret += 2.0 * PI;
  return ret;
}

#define N 1001

bool comp( const PDI &a, const PDI &b ) {
  if ( feq( a.first, b.first ) ) return a.second < b.second;
  return a.first < b.first;
}

int main() {
  int n, m;
  P st[N][2], c;
  PDI q[2222];

  while ( scanf( "%d", &n ), n ) {
    REP( i, n ) {
      st[i][0].eat(); st[i][1].eat();
    }
    c.eat();
    m = 0;
    REP( i, n ) {
      if ( !ccw( c, st[i][0], st[i][1] ) ) swap( st[i][0], st[i][1] );
      st[i][0] = st[i][0] - c;
      st[i][1] = st[i][1] - c;
      double s = ang( st[i][0] ), t = ang( st[i][1] );
      if ( s < t ) {
        q[m++] = PDI( s, 0 );
        q[m++] = PDI( t, 1 );
      } else {
        q[m++] = PDI( s, 0 );
        q[m++] = PDI( 2.0 * PI, 1 );
        q[m++] = PDI( 0.0, 0 );
        q[m++] = PDI( t, 1 );
      }
    }

    sort( q, q + m, comp );
    int ans = 0, cur = 0;
    REP( i, m ) {
      if ( q[i].second ) cur--;
      else ans = max( ans, ++cur );
    }
    printf( "%d\n", ans ); 
  }

	return 0;
}

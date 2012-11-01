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

#define N 22222

bool comp_x( const P &a, const P &b ) {
  return a.x < b.x;
}

bool comp_y( const P &a, const P &b ) {
  return a.y < b.y;
}

P a[N], b[N];

double solve( int s, int t ) {
  if ( s == t ) return 1e20;
  else if ( s == t - 1 ) {
    if ( a[s].y > a[t].y ) swap( a[s], a[t] );
    return ( a[s] - a[t] ).mag();
  }

  int mid = ( s + t ) >> 1, bn = 0;
  double dl = solve( s, mid ), dr = solve( mid + 1, t ), d = min( dl, dr ), mx = ( a[mid].x + a[mid + 1].x ) / 2;
  inplace_merge( a + s, a + mid + 1, a + t + 1, comp_y );

  for( int i = s; i <= t; i++ ) 
    if ( a[i].x > mx - d - EPS && a[i].x < mx + d + EPS ) b[bn++] = a[i];

  double ans = d;

  for( int i = 0; i < bn; i++ ) 
    for( int j = i + 1; j < bn && b[j].y < b[i].y + d + EPS; j++ ) 
      ans = min( ans, ( b[i] - b[j] ).mag() );

  return ans;
}

double ClosestPair( P p[], int n ) {
  for( int i = 0; i < n; i++ ) 
    a[i] = p[i];
  sort( a, a + n, comp_x );
  return solve( 0, n - 1 );
}

P p[N];
int n;

int main() {
  while( scanf( "%d", &n ), n ) {
    REP( i, n ) p[i].eat();
    double ans = ClosestPair( p, n );
    if ( ans > 10000.0 - EPS ) puts( "INFINITY" );
    else printf( "%.4f\n", ans + EPS );
  }
	return 0;
}

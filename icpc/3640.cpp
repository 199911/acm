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

#define N 555

double ps[N], lw[N][N], L, x[N], y[N];
int n, tc;

double cut( double l, double r ) {
  int a = lower_bound( x, x + n + 1, l ) - x, b = upper_bound( x, x + n + 1, r ) - x - 1; 
  double ly, ry;
  ly = y[a - 1] + ( l - x[a - 1] ) * ( y[a] - y[a - 1] ) / ( x[a] - x[a - 1] );
  ry = y[b] + ( r - x[b] ) * ( y[b + 1] - y[b] ) / ( x[b + 1] - x[b] );
  double ans = ps[b] - ps[a], fe = lw[a][b];
  ans += ( x[a] - l ) * ( y[a] + ly ) * 0.5;
  ans += ( r - x[b] ) * ( x[b] + ry ) * 0.5;
  fe = min( fe, min( ly, ry ) );
  ans -= fe * ( r - l );

  return ans;
}


int main() {
  scanf( "%d", &tc );
  while( tc-- ) {
    scanf( "%d%lf", &n, &L );
    for( int i = 0; i < n; i++ ) 
      scanf( "%lf%lf", &x[i], &y[i] );
    x[n] = 1e10;
    ps[0] = 0.0;
    for( int i = 1; i < n; i++ ) { 
      ps[i] = ps[i - 1] + ( x[i] - x[i - 1] ) * ( y[i] + y[i - 1] ) * 0.5;
      lw[i][i] = y[i];
    }

    for( int l = 1; l < n; l++ ) 
      for( int i = 0; i < n - l; i++ ) 
        lw[i][i + l] = min( lw[i][i + l - 1], y[i] );

    for( int i = 0, j = 0; j < n;  

  }
	return 0;
}

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

	double mag() const { return sqrt( x * x + y * y ); }
	double mag2() const { return x * x + y * y; }

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

/**
	* Largest Empty Convex Polygon 
	* Motivation: 
	*		Given n nail on a wood board, what's the maximum area we can enclose using a rope
	*	Complexity: O( n^3 )
	* Idea: Fix the topmost then rightmost point, then fix the first edge, then backward dp using the second edge
	*/

#define N 333

P a[N];
int n;

bool comp( const P &a, const P &b ) {
	double crx = a ^ b;
	return crx > EPS || ( crx > -EPS && a.mag2() < b.mag2() );
}

double sweep( P tp ) {
	P c[N];
	int cn = 0;
	double ret = 0.0, dp[N][N];

	for( int i = 0; i < n; i++ ) 
		if ( a[i].y < tp.y - EPS || ( a[i].y < tp.y + EPS && a[i].x < tp.x ) ) 
			c[cn++] = a[i] - tp;

	if ( cn < 2 ) return 0.0;

	sort( c, c + cn, comp ); 

	for( int i = 0; i < cn; i++ ) for( int j = 0; j < cn; j++ ) dp[i][j] = 0.0;

	for( int i = 1; i < cn; i++ ) {
		int j = i - 1; while ( j > 0 && fabs( c[i] ^ c[j] ) < EPS ) j--;

		int ev[N], nev = 0;

		while( j >= 0 ) {
			double v = 0.5 * ( c[i] ^ c[j] );
			int k = j - 1;
			while( k >= 0 && Ccw( c[i], c[j], c[k] ) ) k--;
			if ( k >= 0 ) v += dp[j][k];
			
			if ( v > ret ) ret = v;
			if ( fabs( c[i] ^ c[i - 1] ) > EPS && v > dp[i][j] ) dp[i][j] = v;

			ev[nev++] = j;
			j = k;
		}

		if ( fabs( c[i] ^ c[i - 1] ) > EPS ) 
			for( int j = nev - 2; j >= 0; j-- ) 
				if ( dp[i][ev[j + 1]] > dp[i][ev[j]] ) 
					dp[i][ev[j]] = dp[i][ev[j + 1]];
	}

	return ret;
}

int main() {
	return 0;
}

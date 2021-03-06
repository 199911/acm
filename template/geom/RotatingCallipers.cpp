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
	return feq( ( b - a ).mag() + ( c - b ).mag(), ( a - c ).mag() );
}

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

bool comp_angle( P a, P b ) {
	if ( up(a) ^ up(b) ) return up(a);
	return ( a ^ b ) > EPS; 
}

// build data structure such that given the direction of caliper, return the vertex it goes through

#define N 111111

P ds[N];
int stt = -1, sz;

void build( P p[], int n ) {
	P minP = p[1] - p[0];
	stt = 0;
	sz = n;
	REP(i, n) {
		if ( comp_angle(p[(i+1)%n] - p[i], minP) ) {
			minP = p[(i+1)%n] - p[i];
			stt = i;
		}
	}
	FOR(i, stt, stt + n) {
		ds[i-stt] = p[(i+1)%n] - p[i%n];
	}
}

int query( P q ) {
	return ( lower_bound( ds, ds + sz, q, comp_angle) - ds + stt) % sz;
}

P p[N];
int n;

int main() {
	scanf("%d", &n);
	REP(i, n) p[i].eat();
	build(p, n);
	REP(i, sz) ds[i].out();
	puts( "" );

	while(1) {
		P q; q.eat();
		printf("sol = ");
		p[query(q)].out();
		puts("");
	}

	return 0;
}

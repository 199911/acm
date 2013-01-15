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
	bool operator<( const P p) const { return x != p.x ? x < p.x : y < p.y; }

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

bool ccw(P a, P b, P c) {
	return area(a, b, c) > -EPS;
}

bool Ccw(P a, P b, P c) {
  return area(a, b, c) > EPS;
}

#define N 10000

int hull(P p[], int n, P ch[], int &hn){
	sort(p, p + n);
	hn = 0;
	for(int i = 0; i < n; i++) {
		while( hn >= 2 && !Ccw(ch[hn - 2], ch[hn - 1], p[i]) ) hn--;
		ch[hn++] = p[i];
	}
	for(int S = hn, i = n - 2; i > 0; i--) {
		while( hn > S && hn >= 2 && !Ccw( ch[hn - 2], ch[hn - 1], p[i])) hn--;
		ch[hn++] = p[i];
	}
}

int main() {
	return 0;
}

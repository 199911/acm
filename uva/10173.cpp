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
#define INF 1e20
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

// Given a convex polygon, find the area of its smallest bounding rectangle

double rectA(P a, P b, P c, P d, P e) {
	double h = ((b - a) ^ (d - a))/(b - a).mag();
	double w1 = ((b - a) * (c - a))/(b - a).mag();
	double w2 = ((b - a) * (e - a))/(b - a).mag();
	return fabs(h * (w1 - w2));
}

double bndRect(P p[], int n) {
	int sl = -1;
	double minDot = INF;
	REP(i, n) {
		double cur = (p[1] - p[0]) * (p[i] - p[0]);
		if ( cur < minDot ) {
			minDot = cur;
			sl = i;
		}
	}

	double minA = INF;
	for(int i = 0, j = 1, k = 1, l = sl; i < n; i++) {
		// update right pointer j
		double last = -INF;
		int up = 0;

		while(true) {
			double cur = (p[(i+1)%n] - p[i]) * (p[j%n] - p[i]);
			if ( cur < last + EPS) break;
			last = cur;
			j++; up = 1;
		}
		if ( up ) j--;

		// update up pointer k
		last = -INF; up = 0;
		while(true) {
			double cur = (p[(i+1)%n] - p[i]) ^ (p[k%n] - p[i]);
			if ( cur < last + EPS) break;
			last = cur;
			k++; up = 1;
		}
		if ( up ) k--;

		// update left pointer l
		last = INF; up = 0;
		while(true) {
			double cur = (p[(i+1)%n] - p[i]) * (p[l%n] - p[i]);
			if ( cur > last - EPS) break;
			last = cur;
			l++; up = 1;
		}
		if ( up ) l--;

		double ra = rectA(p[i], p[(i+1)%n], p[j%n], p[k%n], p[l%n]);
		minA = min(minA, ra);
	}
	return minA;
}

int hull(P p[], int n, P ch[], int &hn){
	sort(p, p + n);
	hn = 0;
	for(int i = 0; i < n; i++) {
		while( hn >= 2 && !ccw(ch[hn - 2], ch[hn - 1], p[i]) ) hn--;
		ch[hn++] = p[i];
	}
	for(int S = hn, i = n - 2; i > 0; i--) {
		while( hn >= S && hn >= 2 && !Ccw( ch[hn - 2], ch[hn - 1], p[i])) hn--;
		ch[hn++] = p[i];
	}
}

#define N 111111

int n, hn;
P p[N], h[N];

int main() {
	while(scanf("%d", &n), n) {
		REP(i, n) p[i].eat();
		if ( n <= 2 ) {
			printf("%.4f\n", 0.0);
			continue;
		}
		hull(p, n, h, hn);

		double ans = bndRect(h, hn);
		printf("%.4f\n", ans);
	}
	return 0;
}

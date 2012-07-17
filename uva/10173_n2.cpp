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

#define N 111111

int n, hn;
P p[N], h[N];

int main() {
	while(scanf("%d", &n), n) {
		REP(i, n) p[i].eat();
		hull(p, n, h, hn);

		int fl = 0;
		double ar = 1e16;
		double h1 = 0.0, h2 = 0.0, w1 = 0.0, w2 = 0.0;

		if( hn < 3 ) {
			puts("0.0000");
			continue;
		}

		REP(i, hn) {
			P a = h[i], b = h[(i+1)%n];

			REP(j, n) {
				P c = p[j];

				h1 = max(h1, (b - a).nor() ^ (c - a));
				h2 = min(h2, (b - a).nor() ^ (c - a));
				w1= max(w1, (b - a).nor() * (c - a));
				w2= min(w2, (b - a).nor() * (c - a));
			}

			double cur = (h1 - h2) * (w1 - w2);
			if ( fl ) ar = min(ar, cur);
			else ar = cur, fl = 1;
		}

		printf("%.4f\n", ar);
	}
	return 0;
}

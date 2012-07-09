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
  P rrot() { return P( y, -x); }
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

bool lli( P a, P b, P c, P d, P &res ) {
	if( feq( ( b - a ) ^ ( d - c ), 0.0 ) ) return false;
	res = a + ( b - a ) * ( area( c, d, a )  / ( area( c, d, a ) - area(c, d, b) ) );
	return true;
}

bool up( P a ) {
  return a.y == 0.0 ? a.x > 0.0 : a.y > 0;
}

#define N 11111

P hp[N][2], res[N];
int hn, rn;

bool comp( const int &a, const int &b ) {
  P pa = hp[a][1] - hp[a][0], pb = hp[b][1] - hp[b][0];
  if ( up(pa) ^ up(pb) ) return up(pa);
  if ( feq(pa ^ pb, 0.0) ) return ccw( hp[b][0], hp[b][1], hp[a][0]);
  return ccw( P(0.0, 0.0), pa, pb);
}

void hpi() {
  int a[N], q[N], qh, qt, pqh, pqt, fl = 0;
  P pq[N], lt;
  REP(i, hn) a[i] = i;

  sort(a, a + hn, comp);

  rn = qh = qt = 0;
  pqh = pqt = 0;

  REP(i, hn){
    if ( qt - qh >= 1 && feq( ( hp[a[i]][1] - hp[a[i]][0] ) ^ ( hp[q[qt-1]][1] - hp[q[qt-1]][0]), 0.0 ) ) continue;
    if ( fl == 1 && ccw( hp[a[i]][0], hp[a[i]][1], lt) ) continue; 
    while( qt - qh >= 2 && !ccw( hp[a[i]][0], hp[a[i]][1], pq[pqt-1])) qt--, pqt--;
    while( qt - qh >= 2 && !ccw( hp[a[i]][0], hp[a[i]][1], pq[pqh])) pqh++, qh++; 
    q[qt++] = a[i];
    if( qt - qh >= 2 ) lli( hp[q[qt-1]][0], hp[q[qt-1]][1], hp[q[qt-2]][0], hp[q[qt-2]][1], pq[pqt++]);
    if ( qh != qt && ( ( ( hp[q[qh]][1] - hp[q[qh]][0] ) ^ (hp[a[i]][1] - hp[a[i]][0]) ) < - EPS ) ) {
      fl = 1;
      lli(hp[q[qh]][0], hp[q[qh]][1], hp[a[i]][0], hp[a[i]][1], lt);
    }
  }

  rn = 0;
  res[rn++] = lt;
  FOR(i, pqh, pqt) {
    res[rn++] = pq[i];
  }

}

int main() {
	return 0;
}

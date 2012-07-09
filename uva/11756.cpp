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

#define INF 1e9
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
	void out() { printf( "%f, %f ", x, y ); }

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

bool lli( P a, P b, P c, P d, P &res ) {
	if( feq( ( b - a ) ^ ( d - c ), 0.0 ) ) return false;
	res = a + ( b - a ) * ( area( c, d, a )  / ( area( c, d, a ) - area(c, d, b) ) );
	return true;
}

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

double parea( P p[], int n ) {
  double ret = 0.0;
  REP(i, n) ret += area( P(0.0, 0.0), p[i], p[(i + 1) % n]);
  return fabs( ret );
}

/**
  * O(nlogn) half plane intersection
  * zzy's method
  *   sweep one round, no merge convex hull
  **/

#define N 111111

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

#ifdef DEBUG
  REP(i, hn){
    printf("a[%d] = %d\n", i, a[i]);
    hp[a[i]][0].out();
    hp[a[i]][1].out();
    puts("");
  }
#endif

  rn = qh = qt = 0;
  pqh = pqt = 0;

  REP(i, hn){
    // paralell half plane
#ifdef DEBUG
    printf("%d:\n", i);
    printf("[%d, %d]\n", qh, qt);
    FOR(x, qh, qt) {
      printf("%d ", q[x]);
    }
    puts( "" );
#endif
    if ( qt - qh >= 1 && feq( ( hp[a[i]][1] - hp[a[i]][0] ) ^ ( hp[q[qt-1]][1] - hp[q[qt-1]][0]), 0.0 ) ) continue;
    // already satisfied
    if ( fl == 1 && ccw( hp[a[i]][0], hp[a[i]][1], lt) ) {
      continue; 
    }
    while( qt - qh >= 2 && !Ccw( hp[a[i]][0], hp[a[i]][1], pq[pqt-1])) qt--, pqt--;
    while( fl && qt - qh >= 2 && !Ccw( hp[a[i]][0], hp[a[i]][1], pq[pqh])) {
      pqh++, qh++; 
      lli( hp[a[i]][0], hp[a[i]][1], hp[q[qh]][0], hp[q[qh]][1], lt);
    }
    q[qt++] = a[i];
    if( qt - qh >= 2 ) lli( hp[q[qt-1]][0], hp[q[qt-1]][1], hp[q[qt-2]][0], hp[q[qt-2]][1], pq[pqt++]);
    if ( qh != qt && ( ( ( hp[q[qh]][1] - hp[q[qh]][0] ) ^ (hp[a[i]][1] - hp[a[i]][0]) ) < - EPS ) ) {
      fl = 1;
      lli(hp[q[qh]][0], hp[q[qh]][1], hp[a[i]][0], hp[a[i]][1], lt);
    }
    /*
    printf("[%d, %d]\n", qh, qt);
    FOR(x, qh, qt) {
      printf("%d ", q[x]);
    }
    puts( "" );
    */
  }

  rn = 0;
  res[rn++] = lt;
  FOR(i, pqh, pqt) {
    res[rn++] = pq[i];
  }
}

P ln[N][2];
int n;

int main() {
  int cas;
  scanf( "%d", &cas );
  while (cas--) {
    double xl, xr, yt = -INF, yb = INF;
    double ta, ba;
    P ll[2], rl[2];
    scanf( "%d", &n );
    int cnt = 0;
    REP(i, n) {
      ln[cnt][0].eat();
      ln[cnt][1].eat();
      if( !feq(ln[cnt][0].x, ln[cnt][1].x) ) cnt++;
    }
    scanf( "%lf%lf", &xl, &xr );

    n = cnt;

    ll[0] = P( xl, 0.0 );
    ll[1] = P( xl, 1.0 );

    rl[0] = P( xr, 0.0 );
    rl[1] = P( xr, 1.0 );

    // upper part
    REP(i, n) {
      hp[i][0] = ln[i][0];
      hp[i][1] = ln[i][1];
      P t1, t2;
      lli(hp[i][0], hp[i][1], ll[0], ll[1], t1);
      lli(hp[i][0], hp[i][1], rl[0], rl[1], t2);
      /*
      printf("t! ");
      t1.out(); t2.out();
      puts( "" );
      */
      yt = max(yt, max(t2.y, t1.y));
      yb = min(yb, min(t1.y, t2.y));
      if( fgt(hp[i][0].x, hp[i][1].x) ) swap(hp[i][0], hp[i][1]);
    }
    hn = n + 3;
    hp[n][0] = P( xr, yt );
    hp[n][1] = P( xl, yt );

    hp[n+1][0] = rl[0];
    hp[n+1][1] = rl[1];

    hp[n+2][0] = ll[1];
    hp[n+2][1] = ll[0];

    hpi();

#ifdef DEBUG
    printf("rn = %d\n", rn);
    REP(i, rn) {
      res[i].out();
      puts("");
    }
#endif

    ta = parea( res, rn );

    // lower part
    REP(i, n) 
      swap(hp[i][0], hp[i][1]);

    hp[n][0] = P( xl, yb );
    hp[n][1] = P( xr, yb );

    hp[n+1][0] = rl[0];
    hp[n+1][1] = rl[1];

    hp[n+2][0] = ll[1];
    hp[n+2][1] = ll[0];

    hpi();

    ba = parea( res, rn );

#ifdef DEBUG
    printf("rn = %d\n", rn);
    REP(i, rn) {
      res[i].out();
      puts("");
    }
    printf("top %f\n", yt);
    printf("but %f\n", yb);
    puts( "-----------------------------------------------------------" );
#endif
    printf("%lf\n", ( yt - yb ) * ( xr - xl ) - ta - ba);
  }

	return 0;
}

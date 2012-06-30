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

#define EPS 1e-6
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
  void out() { printf( "(%.10f, %.10f)", x, y ); }

  P operator+( P p ) { return P( x + p.x, y + p.y ); }
  P operator-( P p ) { return P( x - p.x, y - p.y ); }
  P operator*( double s ) { return P( x * s, y * s ); }
  double operator*( P p ) { return x * p.x + y * p.y; }
  double operator^( P p ) { return x * p.y - y * p.x; }
  bool operator==(P p) { return feq(x, p.x) && feq(y, p.y); }

  double mag() { return sqrt( x * x + y * y ); }
  double mag2() { return x * x + y * y; }

  P nor() { return * this * ( 1.0 / mag() ); }

  P rot() { return P( -y, x ); }
  P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
  P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

double area( P a, P b, P c ) {
  return 0.5 * ((b - a) ^ (c - a));
}

double uarea(P a, P b, P c) {
  return fabs(area(a, b, c));
}

double uarea(P a, P b, P c, P d) {
  return fabs(area(a, c, d) + uarea(b, a, c));
}

bool lli( P a, P b, P c, P d, P &res ) {
  if( feq((b - a) ^ (d - c), 0.0)) return false;
  res = a + (b - a) * (area(c, d, a)  / (area(c, d, a) - area(c, d, b)));
  return true;
}

bool btw( P a, P b, P c ) {
  return feq( ( a - c ).mag(), ( a - b ).mag() + ( b - c ).mag() );
}

bool btw(double a, double b, double c) {
  return fle(a, b) && fle(b, c);
}

void proj(P a, P b, P c, P &d) {
  d = b + (c - b).nor() * (( (a - b) * (c - b)) / (c - b).mag());
}

#define N 100

int n;
P p[N], ha, he;
double A, ans, ps[N];

void update(P a, P b) {
  if( (b - a).mag2() < ans ) {
    ha = a; he = b;
    ans = (b - a).mag2();
  }
}

void find(P a, P b, P c, double s) {
  P e = b + (c - b) * ( s / (uarea(a, b, c)));
  if(btw(b, e, c)) update(e, a);
  else while(1);
}

// find the shortest bisector ef in the 4gon abcd
// where e is on ab and f is on cd such that the 
// area of ebcf is s
void find( P a, P b, P c, P d, double s ) {
  // two edges are parallel
  if( feq((b - a) ^ (d - c), 0.0 ) ) {

    if( s < uarea(b, c, d) ) {
      find(b, c, d, s);
    } else {
      find(d, b, a, s - uarea(b, c, d));
    }

    if( s < uarea(a, b, c )) {
      find(c, b, a, s);
    } else {
      find(a, c, d, s - uarea(a, b, c));
    }

    P e, f;

    proj(a, c, d, e);
    proj(b, c, d, f);

    if( btw(e, f, d) || btw(c, e, f) ) {
    } else {
      if( s < uarea(b, c, f) || s > uarea(a, b, c, d) - uarea(a, e, d) ) {
        return;
      } else {
        update(a, e);
      }
    }

  } else {
    // not parallel
    P e, f, g;

    if(((b - a) ^ (c - d)) > EPS ) {
      swap(a, c); swap(b, d);
      s = uarea(a, b, c, d) - s;
    }

    lli(a, b, d, c, e);

    double ta = s + uarea(e, b, c), sa = uarea(e, e + ( a - e ).nor(), e + ( d - e ).nor());
    double ln = sqrt(ta /sa);

    f = e + ( a - e ).nor() * ln;
    g = e + ( d - e ).nor() * ln;

    if( btw(a, f, b) && btw(c, g, d) ) {
      update(f, g);
    } else {
      if( s < uarea(a, b, c) ) {
        find(c, b, a, s);
      } else {
        find(a, c, d, s - uarea(a, b, c));
      }
      if( s < uarea(b, c, d) ) {
        find(b, c, d, s);
      } else {
        find(d, b, a, s - uarea(b, c, d));
      }
    }
  }
}

double ask(int s, int t) {
  return ps[t] - ps[s] - area(p[0], p[s], p[t % n]);
}

int main() {
  scanf( "%d", &n );
  REP(i, n) p[i].eat();

  ans = 1e9;
  A = 0.0;
  FOR(i, 0, n)
    A += area( p[0], p[i], p[(i + 1) % n] );

  ps[0] = 0.0;
  FOE(i,1,n) {
    ps[i] = ps[i - 1] + area(p[0], p[i - 1], p[i % n]);
  }

  REP(i, n) {
    FOR(j, i + 1, n) {
      if( ask(i + 1, j) < 0.5 * A && ask(i, j+1) > 0.5 * A ) { 
        find(p[i], p[i + 1], p[j], p[(j + 1) % n], 0.5 * A - ask(i + 1, j));
      }
    }
  }

  printf("%.10f\n", sqrt(ans));

  return 0;
}

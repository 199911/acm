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

  P operator+( const P p ) const { return P( x + p.x, y + p.y ); }
  P operator-( const P p ) const { return P( x - p.x, y - p.y ); }
  P operator*( double s ) const { return P( x * s, y * s ); }
  double operator*( const P p ) { return x * p.x + y * p.y; }
  double operator^( const P p ) { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return !feq(x, p.x) ? x < p.x : y < p.y; }
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
  return fge( ((b - a) ^ (c - a)), 0.0 );
}

bool Ccw( P a, P b, P c ) {
  return fgt( ((b - a) ^ (c - a)), 0.0 );
}

bool btw( P a, P b, P c ) {
  return feq( ( b - a ).mag() + ( c - b ).mag(), ( a - c ).mag() );
}

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

// Given a convex polygon, find the area of its smallest bounding rectangle
P piv;

bool comp( const P &a, const P &b ) {
  return Ccw( piv, a, b ) || ccw(piv, a, b) && flt((a - piv).mag2(), (b - piv).mag2());
}

void graham(P p[], int n, P h[], int &hn) {
  piv = P(1e99, 1e99);
  REP(i, n) {
    if ( p[i].y < piv.y || p[i].y == piv.y && p[i].x < piv.x) {
      piv = p[i];
    }
  }
  sort(p, p + n, comp);
  n = unique(p, p + n) - p;

  if ( n <= 1 ) {
    hn = n;
    if( n ) h[0] = p[0];
    return;
  } else if ( area( p[0], p[1], p[n-1]) < EPS ) {
    h[0] = p[0];
    h[1] = p[n-1];
    hn = 2;
    return;
  }

  hn = 0;
  REP(i, n) {
    while( hn >= 2 && !Ccw(h[hn-2], h[hn-1], p[i])) hn--;
    h[hn++] = p[i];
  }
}


void hull(P p[], int &n, P ch[], int &hn){
  sort(p, p + n);
  hn = 0;
  for(int i = 0; i < n; i++) {
    while( hn >= 2 && !Ccw(ch[hn - 2], ch[hn - 1], p[i]) ) hn--;
    ch[hn++] = p[i];
  }
  for(int S = hn, i = n - 2; i >= 0; i--) {
    while( hn > S && hn >= 2 && !Ccw( ch[hn - 2], ch[hn - 1], p[i])) hn--;
    ch[hn++] = p[i];
  }
  hn--;
}

#define N 1111


int main() {

  int n;
  while(scanf("%d", &n), n) {
    P p[N], h[N];
    int hn;

    REP(i, n) p[i].eat();
    hull(p, n, h, hn);

    if( hn < 3 ) {
      puts("0.0000");
      continue;
    }

    double res = 1e10;

    for(int i = 0; i < hn; i++) {
      P a = h[i], b = h[i+1];
      P hr = b - a;
      P vt = hr.rot();
      double d = (b - a).mag();
      double he = -EPS, w1 = -1e10, w2 = 1e10;

      REP(j, hn) {
        P c = h[j];

        double x = fabs((hr ^ (c - a)) / d);
        if ( x > he ) he = x;

        x = (vt ^ c) / d; 
        if ( x > w1 ) w1 = x;
        if ( x < w2 ) w2 = x;

      }

      double w = w1 - w2;
      double cur = he * w;
      if ( cur < res ) res = cur;
    }

    printf("%.4f\n", res);
  }

  return 0;
}

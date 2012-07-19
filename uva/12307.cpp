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
  return fge( ( b - a ) ^ ( c - a ), 0.0 );
}

bool Ccw( P a, P b, P c ) {
  return fgt( (b - a) ^ (c - a), 0.0 );
}

bool btw( P a, P b, P c ) {
  return feq( ( b - a ).mag() + ( c - b ).mag(), ( a - c ).mag() );
}

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

// Given a convex polygon, find the area of its smallest bounding rectangle

void rect(P a, P b, P c, P d, P e, double &ar, double &peri) {
  double l = (b - a).mag2();
  double h = ((b - a) ^ (d - a));
  double w1 = ((b - a) * (c - a));
  double w2 = ((b - a) * (e - a));
  double w = w1 - w2;
  peri = ( w + h ) * 2 / sqrt(l);
  ar = fabs(h * (w1 - w2)) / l;
}

void bndRect(P p[], int n, double &mar, double &mpr) {
  mar = INF;
  mpr = INF;
  for(int i = 0, j = 1, k = 1, l = 1; i < n; i++) {
    while( fgt((p[i + 1] - p[i]) * (p[j + 1] - p[i]), (p[i + 1] - p[i]) * (p[j] - p[i])) ) j = (j + 1) % n;
    while( fgt((p[i + 1] - p[i]) ^ (p[k + 1] - p[i]), (p[i + 1] - p[i]) ^ (p[k] - p[i])) ) k = (k + 1) % n;
    if ( i == 0 ) l = j;
    while( fle((p[i + 1] - p[i]) * (p[l + 1] - p[i]), (p[i + 1] - p[i]) * (p[l] - p[i])) ) l = (l + 1) % n;

    double pr, ar;
    rect(p[i], p[i + 1], p[j], p[k], p[l], ar, pr);

    mar = min(ar, mar);
    mpr = min(pr, mpr);
    
  }
}

int hull(P p[], int n, P ch[], int &hn){
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

#define N 111111

int n, hn;
P p[N], h[N];

int main() {
  while(scanf("%d", &n), n) {
    REP(i, n) p[i].eat();
    hull(p, n, h, hn);

    if ( hn < 3 ) {
      puts( "0.0000" );
      continue;
    }

    double ar, pr;
    bndRect(h, hn, ar, pr);
    printf("%.2f %.2f\n", ar, pr);
  }
  return 0;
}

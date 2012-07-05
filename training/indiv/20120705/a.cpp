#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define EPS 1e-9

struct P {
  double x, y;
  P() {}
  P(double x, double y): x(x), y(y) {}
  void eat() { scanf( "%lf%lf", &x, &y ); }

  P operator+( P p ) { return P( x + p.x, y + p.y ); }
  P operator-( P p ) { return P( x - p.x, y - p.y ); }
  double operator^( P p ) { return x * p.y - y * p.x; }
};

bool left( P a, P b, P c ) {
  if( a.y > b.y ) swap(a, b);
  return ( ( b - a ) ^ ( c - a ) ) > 0;
}

int main() {
  double tp, bt, lf, rt;
  int n, m, first = 1;
  while( scanf( "%d%d%lf%lf%lf%lf", &n, &m, &lf, &tp, &rt, &bt ), n ) {
    P a[5555][2];
    double x, y;
    a[0][0] = P(lf, bt);
    a[0][1] = P(lf, tp);
    a[n+1][0] = P(rt, bt);
    a[n+1][1] = P(rt, tp);
    for(int i = 1; i <= n; i++) {
      scanf( "%lf%lf", &x, &y );
      a[i][1] = P(x, tp);
      a[i][0] = P(y, bt);
    }

    int fl[5555];
    memset(fl, 0, sizeof(fl)); 
    for(int i = 0; i < m; i++) {
      int up = n + 1, lo = 0;
      P p;
      p.eat();
      while( up > lo + 1 ) {
        int mid = ( up + lo ) / 2;
        if ( left( a[mid][0], a[mid][1], p ) ) {
          up = mid;
        } else {
          lo = mid;
        }
      }
      fl[lo]++;
    }

    if( !first ) puts("");
    first = 0;
    for(int i = 0; i <= n; i++) {
      printf("%d: %d\n", i, fl[i]);
    }
  }

  return 0;
}


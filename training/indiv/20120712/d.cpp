#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#define EPS 1e-9

struct P {
  double x, y;
  P() {}
  P(double x, double y): x(x), y(y) {}
  void eat() { scanf("%lf%lf", &x, &y); }

  P operator+(P p) { return P(x + p.x, y + p.y); }
  P operator-(P p) { return P(x - p.x, y - p.y); }
  double operator^( P p ) { return x * p.y - y * p.x; }
  
  bool operator<( const P p )const { return y != p.y ? y < p.y : x < p.x; }
//  bool operator<( const P p )const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return fabs(x - p.x) < EPS && fabs(y - p.x ) < EPS; }
};

bool Ccw(P a, P b, P c) {
  return ((b - a) ^ (c - a)) > EPS;
}

#define N 1111
P p[N], stk[N];
int n, sn;

int main(){
  int cas;
  scanf( "%d", &cas);
  printf("%d\n", cas);
  while( cas--) {
    scanf ( "%d", &n );
    for(int i = 0; i < n; i++ ) {
      p[i].eat();
    }

    sort(p, p + n);
    sn = 0;

    for(int i = 0; i < n; i++) {
      while( sn >= 2 && !Ccw( stk[sn - 2], stk[sn - 1], p[i])) sn--;
      stk[sn++] = p[i];
    }

    for(int i = n - 2, S = sn; i >= 0; i--) {
      while( sn >= 2 && sn > S && !Ccw( stk[sn-2], stk[sn-1], p[i])) sn--;
      stk[sn++] = p[i];
    }

    printf("%d\n", sn);
    for(int i = 0; i < sn; i++) printf("%.0f %.0f\n", stk[i].x, stk[i].y);

    int xxx; if(scanf( "%d", &xxx ) != EOF ) puts("-1");

  }
  return 0;
}

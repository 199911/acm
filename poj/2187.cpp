#include <cstdio>
#include <algorithm>
using namespace std;

#define LL long long

struct P {
  LL x, y;
  P() {}
  P(LL x, LL y): x(x), y(y) {}
  void eat() { scanf("%lld%lld", &x, &y); }
  void out() { printf("(%lld,%lld)", x, y); }

  P operator+(P p){ return P(x+p.x, y+p.y); }
  P operator-(P p){ return P(x-p.x, y-p.y); }
  LL operator^(P p){ return x*p.y-y*p.x; }

  bool operator<(const P p)const{ return (x!=p.x)?(x<p.x):(y<p.y); }
  bool operator==(const P &p)const{ return x==p.x && y==p.y; }

  LL mag2() { return x*x+y*y; }
};

#define N 100000

#define FOR(i,a,b) for(int i=(a); i<(b); i++)
#define REP(i,n) FOR(i,0,n)
#define EPS 1e-9

bool ccw(P a, P b, P c){ return ((b-a)^(c-a))>0; }
P p[50001], h[50001];
int main() {
  int n;
  scanf("%d", &n);
  for (int i=0;i<n;i++) p[i].eat();
  sort(p,p+n);
  // Build Hull
  int m=0, j=0;
  while(j<n) {
    while(m>=2 && !ccw(h[m-2],h[m-1],p[j])) m--;
    h[m++] = p[j++];
  }
  int nn=m;
  j=n-2;
  while(j>=0) {
    while(m>nn && !ccw(h[m-2],h[m-1],p[j])) m--;
    h[m++] = p[j--];
  }
  --m;
  // Scan Rotationally
  LL ans = -1;
  for(int i = 0, j = 1; i < n; i++ ) {
    LL last = -1; int up = 0;
    while(true) {
      LL cur = ( h[(i+1)%n] - h[i] ) ^ ( h[j%n] - h[i] );
      if ( cur <= last ) break;
      last = cur; up = 1;
      j++;
    }
    if ( up ) j--;
    for(int k = j; ( h[(i+1)%n] - h[i] ) ^ (h[k%n] - h[i]); k++ ) {
      LL cur1 = ( h[k%n] - h[i] ).mag2();
      LL cur2 = ( h[k%n] - h[(i+1)%n] ).mag2();
      ans = max(ans, max(cur1, cur2));
    }
  }
  printf("%d\n", ans); // Return sq(FarthestPairDistance)
  return 0;
}

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

#define N 300
#define M 20000
#define F 300

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

  double mag() { return sqrt( x * x + y * y ); }
  double mag2() { return x * x + y * y; }

  P nor() { return * this * ( 1.0 / mag() ); }

  P rot() { return P( -y, x ); }
  P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
  P rot( double th ) { return rot( sin( th ), cos( th ) ); }
} V[N];

double area( P a, P b, P c ) {
  return 0.5 * ( ( b - a ) ^ ( c - a ) );
}

bool ccw( P a, P b, P c ) {
  return fge( area(a, b, c), 0.0 );
}

int hd[N], to[M], nt[M], n, m;        // graph structure
int ne[M], pe[M], oc[F], fn;
int k, ans;

void init(){
  memset(hd, -1, sizeof(hd));
  memset(nt, -1, sizeof(nt));
  memset(ne, -1, sizeof(ne));
  memset(nt, -1, sizeof(nt));
  m = 0;
  fn = 0;
}

// becareful not to create redundant edges
void add(int a, int b) {
  to[m] = b; nt[m] = hd[a]; hd[a] = m++;
  to[m] = a; nt[m] = hd[b]; hd[b] = m++;
}

int piv;

bool comp(int &a, int &b) {
  P c = V[a] - V[piv], d = V[b] - V[piv];
  if ()
}

void build() {
  // build next/prev edge link
  // O(mn) create link
  REP(i, m ) {
    // edge (u, v)
    int u = to[(i^1)], v = to[i];
    for(int e = hd[v]; e != -1; e = nt[e]) {
      if( to[e] == u )  continue; 
      if( ne[i] == -1 ) {
        ne[i] = e; pe[e] = i;
      } else {
        if( ccw(V[u], V[v], V[to[ne[i]]]) ) {
          if( ccw(V[u], V[v], V[to[e]]) && ccw(V[v], V[to[ne[i]]], V[to[e]]) ) {
            ne[i] = e; pe[e] = i;
          }
        } else {
          if( ccw(V[u], V[v], V[to[e]]) || ccw(V[v], V[to[ne[i]]], V[to[e]]) ) {
            ne[i] = e; pe[e] = i;
          }
        }
      }
    }
    if( ne[i] == -1 ){
      ne[i] = i^1;
      pe[i^1] = i;
    }
  }

  // O(n log n) create link
  REP(v, n) {
    int a[N];
    for( int e = hd[v]; e != -1; e = nt[v] ) {
      int u = to[v];
      
    }
  }

  // build face link
  bool us[M]; 
  memset(us, 0, sizeof(us));
  REP(i, m) {
    if( !us[i] ) {
      oc[fn++] = i;
      for(int p = i; !us[p]; p = ne[p] ) {
        cnt++;
        us[p] = true;
        A += area(V[to[i^1]], V[to[p^1]], V[to[p]]);
      }
    }
  }
}

int main() {
  return 0;
}

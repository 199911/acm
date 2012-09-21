#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }


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
};

double area( P a, P b, P c ) {
  return 0.5 * ( ( b - a ) ^ ( c - a ) );
}

bool ccw( P a, P b, P c ) {
  return fge( area(a, b, c), 0.0 );
}

P V[N];
int hd[N], to[M], nt[M], n, m;        // graph structure
int ne[M], pe[M], oc[F], fn;
double fa[F];

void init(){
  memset(hd, -1, sizeof(hd));
  memset(nt, -1, sizeof(nt));
  memset(ne, -1, sizeof(ne));
  memset(nt, -1, sizeof(nt));
  m = 0;
  fn = 0;
}

void add(int a, int b) {
  // becareful not to create redundant edges
  if( a > b ) return;
  to[m] = b; nt[m] = hd[a]; hd[a] = m++;
  to[m] = a; nt[m] = hd[b]; hd[b] = m++;
}

int piv;

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

bool comp(const int &x, const int &y) {
  P a = V[to[x]], b = V[to[y]], pv = V[piv];
  if ( up( a - pv ) ^ up( b - pv ) ) {
    return up( a - pv );
  } else {
    return ccw( pv, a, b );
  }
}

void build_slow() {
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
}

void build() {
  // O( m log n ) create link
  REP(v, n) {
    int a[N], k = 0;
    for( int e = hd[v]; e != -1; e = nt[e] ) {
      int u = to[e];
      a[k++] = e;
    }
    piv = v;
    sort(a, a + k, comp);
    REP(i, k) {
      ne[a[i]^1] = a[(i + k - 1 )% k];
      pe[ne[a[i]^1]] = a[i]^1;
    }
  }

  // build face link
  bool us[M]; 
  memset(us, 0, sizeof(us));
  REP(i, m) {
    if( !us[i] ) {
      fa[fn] = 0;
      oc[fn] = i;
      for(int p = i; !us[p]; p = ne[p] ) { 
        us[p] = true;
        fa[fn] += area( P(0.0, 0.0), V[to[p]], V[to[ne[p]]]);
      }
      fn++;
    }
  }
}

int main() {
  init();

  scanf( "%d", &n );

  REP( i, n ) {
    int a, b, dg;
    scanf( "%d", &a ); 
    a--;

    V[a].eat();

    scanf( "%d", &dg );
    REP( j, dg ) {
      scanf( "%d", &b ); b--;
      add( a, b );
    }
  }

  build();

  printf( "%d\n", fn );

  return 0;
}

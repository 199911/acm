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
#include <map>
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
  void out() { printf( "(%.1f, %.1f)", x, y ); }

  P operator+( P p ) { return P( x + p.x, y + p.y ); }
  P operator-( P p ) { return P( x - p.x, y - p.y ); }
  P operator*( double s ) { return P( x * s, y * s ); }
  double operator*( P p ) { return x * p.x + y * p.y; }
  double operator^( P p ) { return x * p.y - y * p.x; }
  bool operator<( const P &p ) const { return feq( x, p.x ) ? flt( y, p.y ) : flt( x, p.x ); }

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

#define N 111
#define M ( 2 * N * N ) 
#define F M

int hd[M], to[M], nt[M], n, m;        // graph structure
int ne[M], pe[M], oc[F], ec[F], fn;
double fa[F];
P V[M];

void init(){
  memset(hd, -1, sizeof(hd));
  memset(nt, -1, sizeof(nt));
  memset(ne, -1, sizeof(ne));
  memset(nt, -1, sizeof(nt));
  n = 0;
  m = 0;
  fn = 0;
}

void add(int a, int b) {
  // becareful not to create redundant edges
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

void build() {
  // O( m log n ) create link
  REP(v, n) {
    int a[M], k = 0;
    for( int e = hd[v]; e != -1; e = nt[e] ) {
      int u = to[e];
      a[k++] = e;
    }
    piv = v;
    sort(a, a + k, comp);
    REP(i, k) {
      ne[a[i]^1] = a[(i + k - 1)% k];
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
      ec[fn] = 0;
      for(int p = i; !us[p]; p = ne[p] ) { 
        ec[fn]++;
        us[p] = true;
        fa[fn] += area( P(0.0, 0.0), V[to[p]], V[to[ne[p]]]);
      }
      fn++;
    }
  }
}


P p[N];
int pn;

bool float_equal( const double &a, const double &b ) {
  return feq( a, b );
}

typedef map<P, int> MPI;
typedef pair<P, int> PPI;

void build_planar() {
  MPI mp;
  mp.clear();
  init();

  for ( int i = 0; i < pn; i++ ) { 
    mp.insert( PPI(p[i], i ) );
    V[n++] = p[i];
  }

  for ( int i = 0; i < pn; i++ ) {
    double S[N]; 
    int sn = 0, dn = 0, D[N];
    P a = V[i], b = V[(i + 1) % pn];
    for ( int j = 2; j < pn - 1; j++ ) {
      P c = V[(i + j) % pn], d = V[(i + j + 1) % pn];
      double s = ((c - a) ^ (d - c)) / ((b - a) ^ (d - c)); 
      double t = ((a - c) ^ (b - a)) / ((d - c) ^ (b - a));
      if ( s > EPS && s < 1 - EPS && t > EPS && t < 1 - EPS ) {
        S[sn++] = s;
      }
    }
    sort( S, S + sn );
    sn = unique( S, S + sn, float_equal ) - S;
    D[dn++] = i;
    for ( int j = 0; j < sn; j++ ) {
      P nw = a + (b - a) * S[j];
      MPI::iterator it = mp.find( nw );
      if ( it == mp.end() ) {
        mp.insert( PPI( nw, n) );
        V[n] = nw;
        D[dn++] = n++;
      } else {
        D[dn++] = it->second;
      }
    }
    D[dn++] = (i + 1) % pn;
    
    for ( int j = 0; j < dn - 1; j++ ) {
      add( D[j], D[j + 1] );
    }
  }
}

int main() {
  return 0;
}

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
#include <map>
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

bool Ccw( P a, P b, P c ) {
  return fgt( area(a, b, c), 0.0 );
}

bool btw( P a, P b, P c ) {
  if ( !feq( (b - a) ^ (c - a), 0.0 ) ) return 0;
  double s = (b - a) * (c - a);
  return fge( s, 0.0 ) && fle( s, (c - a).mag2() );
}

#define N 4444
#define M (4444*2)
#define F (666)

int hd[N], to[M], nt[M], n, en;        // graph structure
int ne[M], pe[M], ff[M * 2], oc[F * 2], dd[F * 2], op[F * 2], fn;
double fa[F * 2];
P V[N];

void init(){
  memset(hd, -1, sizeof(hd));
  memset(nt, -1, sizeof(nt));
  memset(ne, -1, sizeof(ne));
  memset(nt, -1, sizeof(nt));
  fn = 0;
  en = 0;
}

void add(int a, int b) {
  // becareful not to create redundant edges
  to[en] = b; nt[en] = hd[a]; hd[a] = en++;
  to[en] = a; nt[en] = hd[b]; hd[b] = en++;
}

int piv;

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

int in_poly( P p[], int n, P x ) {
   REP( i, n ) 
     if ( btw( p[i], x, p[(i + 1) % n] ) ) return false;
   int sum = 0;
   REP( i, n ) {
     if ( up( p[i] - x ) ^ up( p[(i + 1) % n] - x ) ) 
       sum += Ccw( x, p[i], p[(i + 1) % n] ) ? 1 : -1;
   }
   sum = !!sum;
   return sum;
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
  REP(i, en) {
    if( !us[i] ) {
      fa[fn] = 0;
      oc[fn] = i;
      for(int p = i; !us[p]; p = ne[p] ) { 
        us[p] = true;
        ff[p] = fn;
        fa[fn] += area( P(0.0, 0.0), V[to[p]], V[to[ne[p]]]);
      }
      fn++;
    }
  }

  memset( op, -1, sizeof( op ) );
  for ( int i = 0; i < en ; i += 2 ) {
    int a = i, b = i + 1;
    if ( fa[ff[a]] > EPS && fa[ff[b]] > EPS ) continue; 
    if ( fa[ff[a]] < -EPS ) swap( a, b );
    op[ff[a]] = ff[b];
  }
}

P cap[N];
int k, m;

int main() {
  while ( true ) {
    scanf( "%d %d", &k, &m );
    if ( k == 0 && m == 0 ) break;

    map<P, int> mp;
    REP( i, k ) cap[i].eat();

    mp.clear();
    n = 0;
    init();

    REP( i, m ) {
      P a, b;
      int u, v;
      a.eat(); b.eat();
      map<P, int>::iterator it;

      it = mp.find( a );
      if ( it != mp.end() ) {
        u = it->second;
      } else {
        mp.insert( pair<P, int>( a, n ) );
        u = n;
        V[n++] = a;
      }

      it = mp.find( b );
      if ( it != mp.end() ) {
        v = it->second;
      } else {
        mp.insert( pair<P, int>( b, n ) );
        v = n;
        V[n++] = b;
      }

      add(u, v);
    }
    build();

    int in[F][F], ctr[F], idx[F], cn = 0, sf[F * 2], ct[F], dn[F];
    int q[F], qh, qt;

    CLR( ctr, -1 ); 
    CLR( sf, -1 );
    CLR( dn, 0 );
    qh = qt = 0;

    REP( i, fn ) if ( fa[i] > EPS ) {
      ctr[cn] = i;
      sf[i] = cn++;
    }

    if ( cn != k ) while ( 1 );

    REP( i, cn ) REP( j, k ) in[i][j] = 0;
    REP( fc, cn ) {
      ct[fc] = 0;
      REP( i, k ) {
        int ptr = oc[ctr[fc]], ok, rn = 0;
        P pp[N];
        do {
          pp[rn++] = V[to[ptr]];
          ptr = ne[ptr];
        } while ( ptr != oc[ctr[fc]] );
        ok = in_poly( pp, rn, cap[i] );
        in[fc][i] = ok;
        ct[fc] += ok;
      }
      
      if ( ct[fc] == 1 ) {
        dn[fc] = 1;
        q[qt++] = fc;
      }
    }

    while ( qt > qh ) {
      int c = q[qh++];
      REP( i, k ) if ( in[c][i] ) idx[c] = i; 
      REP( cc, cn ) {
        ct[cc] -= in[cc][idx[c]];
        in[cc][idx[c]] = 0;
        if ( ct[cc] == 1 && dn[cc] == 0) { 
          q[qt++] = cc;
          sf[op[ctr[cc]]] = c;
        }
      }
    }

    int war[F][F];
    memset( war, 0, sizeof(war) );

    for( int i = 0; i < en; i += 2 ) {
      int a = ff[i], b = ff[i + 1];
      if ( sf[a] != -1 && sf[b] != -1 ) {
        war[idx[sf[a]]][idx[sf[b]]] = 1;
        war[idx[sf[b]]][idx[sf[a]]] = 1;
      }
    }

    REP( i, cn ) {
      int cnt = 0;
      REP( j, cn ) 
        if ( war[i][j] ) cnt++;
      printf( "%d", cnt );
      REP( j, cn ) if( war[i][j] ) printf( " %d", j + 1); 
      puts( "" );
    }

  }
  return 0;
}

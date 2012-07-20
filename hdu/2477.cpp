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
#define INF (1<<29)
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
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
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
  return fge( area( a, b, c ), 0.0 );
}

bool Ccw( P a, P b, P c ) {
  return fgt( area( a, b, c ), 0.0 );
}

bool btw( P a, P b, P c ) {
  return feq( ( b - a ).mag() + ( c - b ).mag(), ( a - c ).mag() );
}

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

#define N 50010
#define K 111

int n, k;
P c[N];                         // input param
double r[N]; 
int v[N];
int ma[N*K], mi[N*K];      // tree table
int st[N], sz[N], m;
int root, hd[N], nt[N], to[N], p[N], en;       // tree structure
int ans;

// a contained in b
bool cont( int a, int b ) {
  return (c[a] - c[b] ).mag() < r[b] - r[a] + EPS;
}

void init() {
  memset(hd, -1, sizeof(hd));
  memset(nt, -1, sizeof(nt));
  memset(p, -1, sizeof(p));
  m = 0;
  en = 0;
}

void add(int a, int b) {
  to[en] = b; p[b] = a; nt[en] = hd[a]; hd[a] = en++;
}

// event = 
//    open : top point, with index < n
//    close : bottom point, with index >= n
//  sort events in descreasing y
bool comp_evt( const int &a, const int &b ) {
  double ya = c[a % n].y + ( a < n ? r[a % n] : -r[a % n] );
  double yb = c[b % n].y + ( b < n ? r[b % n] : -r[b % n] );
  if ( !feq(ya, yb) ) return ya > yb;
  if ( (a < n) ^ (b < n) ) {
    return a < n;
  } else {
    return c[a].x > c[b].x;
  }
}

double curY;

// parathesis:
//    open: left intersection, with index < n
//    close: right intersection, with index >= n

struct comp_clr {
  bool operator() ( const int &a, const int &b ) const {
    double ra = sqrt( r[a % n] * r[a % n] - ( c[a % n].y - curY ) * ( c[a % n].y - curY ) ) + EPS;
    double rb = sqrt( r[b % n] * r[b % n] - ( c[b % n].y - curY ) * ( c[b % n].y - curY ) ) + EPS;
    double xa = c[a % n].x + ( a < n ? -ra : ra );
    double xb = c[b % n].x + ( b < n ? -rb : rb );

    if ( a == b ) return false;
    if ( !feq(xa, xb) ) {
      return xa < xb;
    } else {
      if ( ( a < n ) ^ ( b < n ) ) 
        return a < n;
    }
  }
};

// build tree 
void build() {
  int evt[N*2];
  root = n * 2;
  for (int i = 0; i < 2 * n; i++ ) evt[i] = i; 

  init();

  sort(evt, evt + 2 * n, comp_evt );

  set<int, comp_clr> T;

  for( int i = 0; i < 2 * n; i++ ) {
    if ( evt[i] < n ) {
      // curY
      curY = c[evt[i]].y + r[evt[i]];
      // inserting event
      set<int, comp_clr>::iterator it = T.lower_bound( evt[i] );

      if ( it == T.end() ) { // maximal circle
        add( root, evt[i] );
      } else {
        int b = *it % n;
        if ( cont( evt[i], b )) {
          add( b, evt[i]);
        } else {
          add( p[b], evt[i] );
        }
      }

      T.insert( evt[i] );
      T.insert( evt[i] + n );

    } else {
      // update curY
      curY = c[evt[i]%n].y - r[evt[i]%n];
      T.erase(evt[i] % n);
      T.erase(evt[i] );
    }
  }
}

void dfs( int x ) {
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    dfs( to[e] );
  }

  ma[m] = mi[m] = v[x];
  sz[x] = 1;
  st[x] = m++;

  for( int e = hd[x]; e != -1; e = nt[e] ) {
//    printf("to %d\n", to[e]);
//    printf("sz[%d] = %d\n", to[e], sz[to[e]]);
    for( int i = 0; i < sz[to[e]]; i++ ) {
      if ( i + 1 == sz[x] ) {
        sz[x]++; 
        ma[m] = ma[st[to[e]] + i];
        mi[m] = mi[st[to[e]] + i];
        m++;
      } else {
        ma[st[x]+i+1] = max(ma[st[x]+ i + 1], max(ma[st[x] + i], ma[st[to[e]] + i]));
        mi[st[x]+i+1] = min(mi[st[x]+ i + 1], min(mi[st[x] + i], mi[st[to[e]] + i]));
      }
    }
  }

  /*
  printf("node %d: \n", x);
  for(int i = 0; i < sz[x]; i++) {
    printf("ma[%d] = %d\n", i, ma[st[x] + i]);
    printf("mi[%d] = %d\n", i, mi[st[x] + i]);
  }
  */

  int u = min(k + 1, sz[x]);
  for( int i = 0; i < u; i++ ) {
    ans = max(ans, ma[st[x]+i] - mi[st[x] + min(u - 1, k - i)]);
  }
}

int main() {
  int cas = 1, T;
  scanf( "%d", &T );

  while ( T-- ) {
    scanf("%d%d", &n, &k );
    REP(i, n) {
      c[i].eat();
      scanf( "%lf%d", &r[i], &v[i] );
    }

    build();

    ans = -INF;
    memset(sz, 0, sizeof(sz));
    dfs( root );

    printf("Case %d: %d\n", cas++, ans);
  }

  return 0;
}

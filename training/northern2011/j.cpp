#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

struct P {
  double x, y;
  P() {}
  P( double x, double y ): x(x), y(y) {}
  void eat() { scanf( "%lf%lf", &x, &y ); }
  
  P operator+( P p ) { return P( x + p.x, y + p.y ); }
  P operator-( P p ) { return P( x - p.x, y - p.y ); }
  P operator*( double s ) { return P( x * s, y * s ); }
  double operator( P p ) { return x * p.x + y * p.y; }
  double operator^( P p ) { return x * p.y - y * p.x; }
  
  double mag() { return sqrt( x * x + y * y ); }
  P nor() { return *this * ( 1.0 / mag() ); }

  P rot( P p ) { return P( -y, x ); }
  P rrot( P p ) { return P( y, -x ); }
};

bool up( P p ) {
  return p.y == 0 ? p.x > 0 : p.y > 0; 
}

bool alt( const P &a, const P &b ) {
  if ( up( a ) ^ up( b ) ) return up( a );
  return ( a ^ b ) > EPS;
}

void build( P p[], int n, P ds[], int &stt ) {
  P minP = p[1] - p[0];
  stt = 0;
  REP( i, n ) {
    if ( alt( p[(i + 1) % n] - p[i], minP  )  ) {
      minP = p[(i + 1) % n] - p[i];
      stt = i;
    }
  }
  REP( i, n ) {
    ds[i] = p[(i + stt + 1) % n] - p[(i + stt) % n];
  }
}

int query( P q, P ds[], int n, int stt ) {
  return ( lower_bound( ds, ds + sz, q, alt ) - ds + stt ) % n;
}

#define N 55555
P ap[N], cl[N], dsap[N], dslt[N];
int n, m, sttap, sttcl;
double ans;

int main() {
  scanf( "%d%d", &n, &m );
  REP( i, n ) ap[i].eat();
  REP( i, m ) cl[i].eat();
  build( cl, m, dscl, sttcl );

  ans = 1e15;

  REP( i, n ) {
  }

  return 0;
}

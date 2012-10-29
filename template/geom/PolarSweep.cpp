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

const double PI = 4.0 * atan( 1.0 );

struct P {
  double x, y;
  P() {}
  P( double x, double y ): x(x), y(y) {}
  void eat() { scanf( "%lf%lf", &x, &y ); }
  void out() const { printf( "(%f, %f)", x, y ); }

  P operator+( const P p ) const { return P( x + p.x, y + p.y ); }
  P operator-( const P p ) const { return P( x - p.x, y - p.y ); }
  P operator*( double s ) { return P( x * s, y * s ); }
  double operator*( P p ) const { return x * p.x + y * p.y; }
  double operator^( P p ) const { return x * p.y - y * p.x; }
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
  if ( !feq( ( b - a ) ^ ( c - a ), 0.0 ) ) return 0;
  double s = ( b - a ) * ( c - a );
  return fge( s, 0.0 ) && fle( s, ( c - a ).mag2() );
}

double ang( P a ) {
  double ret = atan2( a.y, a.x );
  if ( ret < -EPS ) ret += 2 * PI;
  return ret;
}

#define N 11111
double curA;

struct E {
  P a, b;
  double st, en;
  int sid;

  E() {}
  E( P a, P b, int sid ): a(a), b(b), sid(sid) { st = ang( a ), en = ang( b ); }

  double getR( double curA ) const {
    P c = P ( cos(curA), sin(curA) );
    double ret =  ( a ^ ( b - a ) ) / ( c ^ ( b - a ) );
    return ret;
  }

  bool operator<( const E &e ) const {
    double s = getR( curA ), t = e.getR( curA );
    return s < t;
  }
};

E st[N];
int n;

bool comp_evt( const int &a, const int &b ) {
  int sa = a / n, sb = b / n, ta = a % n, tb = b % n;
  return ( sa ? st[ta].st : st[ta].en ) < ( sb ? st[tb].st : st[tb].en );
}

int sweep() {
  int q[N * 2], fl[N];
  set<E> T;
  REP( i, 2 * n ) q[i] = i;
  sort( q, q + 2 * n, comp_evt );

  REP( i, n ) fl[i] = 0;
  T.clear();
  curA = 0.0;

  REP( i, 2 * n ) {
    int id = q[i] % n, op = q[i] / n;
    if ( op ) {
      fl[id] = 1;
    } else {
      if ( !fl[id] ) {
        T.insert( st[id] );
      }
    }
  }

  int ans = 0;
  REP( i, n ) fl[i] = 0;
  REP( i, 2 * n ) {
    int id = q[i] % n, op = q[i] / n;
    E cur = st[id];

    if ( op ) {
      curA = cur.st;
      T.insert( cur );

      set<E>::iterator it = T.begin();
      if ( fl[it->sid] == 0 ) {
        ans++;
        fl[it->sid] = 1;
      }
    } else {
      curA = cur.en;
      T.erase( cur );

      set<E>::iterator it = T.begin();
      if ( it != T.end() && fl[it->sid] == 0 ) {
        ans++;
        fl[it->sid] = 1;
      }
    }
  }

  return ans;
}

int main() {
  while ( scanf( "%d", &n ) > EOF ) {
    P c;
    c.eat();
    REP( i, n ) {
      P a, b;
      a.eat(); b.eat();
      if ( !Ccw( c, a, b ) ) swap ( a, b );
      st[i] = E( a - c, b - c, i );
    }
    printf( "%d\n", sweep() );
  }

  return 0;
}

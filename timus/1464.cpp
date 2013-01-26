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

#define EPS 1e-8
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
  void out() const  { printf( "(%f, %f)", x, y ); }

  P operator+( const P p ) const { return P( x + p.x, y + p.y ); }
  P operator-( const P p ) const { return P( x - p.x, y - p.y ); }
  P operator*( const double s ) const { return P( x * s, y * s ); }
  double operator*( const P p ) const { return x * p.x + y * p.y; }
  double operator^( const P p ) const { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return feq( x, p.x ) && feq( y, p.y ); }

  double mag() const { return sqrt( x * x + y * y ); }
  double mag2() const { return x * x + y * y; }

  P nor() { return * this * ( 1.0 / mag() ); }

  P rot() { return P( -y, x ); }
  P rrot() { return P( y, -x ); }
  P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
  P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

double area( P a, P b, P c ) {
  return 0.5 * (( b - a ) ^ ( c - a ));
}

double area( double a1, double r1, double a2, double r2 ) {
  double a = a2 - a1;
  return r1 * r2 * sin( a ) * 0.5;
}

bool Ccw( P a, P b, P c ) {
  return ((  b - a ) ^ ( c - a ) ) > EPS;
}

#define N 55555

double curA;

bool comp( const P &a, const P &b ) {
  if ( fabs( a ^ b ) > EPS ) return ( a ^ b ) > 0;
  return a.mag() < b.mag();
}

struct S {
  P a, b;
  int idx;

  S() {}
  S( P a, P b, int idx ): a(a), b(b), idx(idx) {}

  double getR( double A ) const {
    P c = P( cos( A ), sin( A ) );
    return ( a ^ ( b - a ) ) / ( c ^ ( b - a ) );
  }

  bool operator<( const S &s ) const {
    double x = getR( curA ), y = s.getR( curA );
    if ( a == s.a && b == s.b ) return false;
    if( fabs( x - y ) > EPS ) return x < y;
    else {
      if ( a == s.a ) {
        return area( a, s.b, b ) > EPS;
      } else if ( a == s.b ) {
        return true;
      } else if ( b == s.a ) {
        return false;
      } else if ( b == s.b ) {
        return area( b, a, s.a ) > EPS;
      } else {
        return false;
      }
    }
  }
} Sg[N];

struct E {
  P a;
  bool ins;
  int ptr;

  E() {}
  E( P a, bool ins, int ptr ): a(a), ins(ins), ptr(ptr) {} 

  bool operator<( const E &e ) const {
    double A = atan2( a.y, a.x ), B = atan2( e.a.y, e.a.x );
    if ( fabs( A - B ) > EPS ) return A < B;
    if ( ins ^ e.ins ) return ins;
    return ptr < e.ptr;
  }
} evt[N * 2];

P p[N], C;
set<S> st;
int n, en;

int main() {
  C.eat();
  scanf( "%d", &n );
  REP( i, n ) {
    p[i].eat();
    p[i] = p[i] - C;
  }

  en = 0;
  REP( i, n ) {
    P a = p[i], b = p[(i + 1) % n];
    if ( fabs( a ^ b ) < EPS ) continue;
    if ( ( a ^ b ) < 0 ) swap( a, b );
    Sg[i] = S( a, b, i );
    evt[en++] = E( a, 1, i );
    evt[en++] = E( b, 0, i );
  }

  sort( evt, evt + en );

  curA = atan2( evt[0].a.y, evt[0].a.x );
  bool op[N], in[N];
  REP( i, en ) {
    if ( evt[i].ins ) op[evt[i].ptr] = 1;
    else if ( !op[evt[i].ptr] ) { 
      in[evt[i].ptr] = 1;
      st.insert( Sg[evt[i].ptr] );
    }
  }

  double ans = 0.0;
  REP( i, en + 1 ) {
    E e = evt[i % en];
    double ang = atan2( e.a.y, e.a.x );

    if ( e.ins ) {
      in[e.ptr] = 1;
      if ( i ) {
        double curR = st.begin()->getR( curA );
        double rad = st.begin()->getR( ang );
        double tmp = area( curA, curR, ang, rad );
        ans += tmp; 
      }
      curA = ang;
      st.insert( Sg[e.ptr] );
    } else {
      in[e.ptr] = 0;
      if ( i ) {
        double rad = st.begin()->getR( ang );
        double curR = st.begin()->getR( curA );
        double tmp = area( curA, curR, ang, rad );
        ans += tmp; 
      }
      st.erase( Sg[e.ptr] ); 
      curA = ang;
    }
  }

  printf( "%.2f\n", ans );

  return 0;
}

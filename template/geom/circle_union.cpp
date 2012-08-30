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
#define REP(i, n) FOR(i, 0, n)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
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
  void out() const  { printf( "(%f, %f)", x, y ); }

  P operator+( const P p ) const { return P( x + p.x, y + p.y ); }
  P operator-( const P p ) const { return P( x - p.x, y - p.y ); }
  P operator*( const double s ) const { return P( x * s, y * s ); }
  double operator*( const P p ) const { return x * p.x + y * p.y; }
  double operator^( const P p ) const { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return feq( x, p.x ) && feq( y, p.y ); }

  double mag() { return sqrt( x * x + y * y ); }
  double mag2() { return x * x + y * y; }

  P nor() { return * this * ( 1.0 / mag() ); }

  P rot() { return P( -y, x ); }
  P rrot() { return P( y, -x ); }
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
  if ( ret < -EPS ) ret += 2.0 * PI;
  return ret;
}
#define N 1111

bool contained( P a, double ra, P b, double rb ) {
  return ra < rb + EPS && ( a - b ).mag2() < SQR( ra - rb ) + EPS;
}

bool intersect( P a, double ra, P b, double rb, double &s, double &t ) {
  if ( ( b - a ).mag2() < SQR( ra - rb ) + EPS || ( b - a ).mag2() > SQR( ra + rb ) - EPS ) 
    return false;
  double rc = ( b - a ).mag();
  double p = 0.5 * ( ra + rb + rc );
  double A = sqrt( p ) * sqrt( p - ra ) * sqrt( p - rb ) * sqrt( p - rc );
  double x = 2 * A / rc;
  double ya = sqrt( ra * ra - x * x ), yb = sqrt( rb * rb - x * x ) ;

  //  printf( "%lf, %lf %lf %lf\n", x, ya, yb, rc);

  //  if ( !feq( rc, ya + yb ) ) printf( "asdf: %.13f\n", ya + yb - rc );

  if ( isnan( ya ) || isnan( yb ) || isnan( A ) ) while ( 1 );

  P u, v;

  if ( !feq( rc, fabs( ya - yb ) ) && !feq( rc, ya + yb ) ) while ( 1 );

  if ( ra < rb - EPS && SQR( ra ) + SQR( rc ) < SQR( rb ) - EPS ) {
    //    if ( !feq( rc, fabs( ya - yb )) ) while ( 1 );
    u = ( b - a ).nor() * ( -ya ) + ( b - a ).nor().rrot() * x;
    v = ( b - a ).nor() * ( -ya ) + ( b - a ).nor().rot() * x;
  } else {
    //    if ( !feq( rc, ya + yb ) ) while ( 1 );
    u = ( b - a ).nor() * ya + ( b - a ).nor().rrot() * x;
    v = ( b - a ).nor() * ya + ( b - a ).nor().rot() * x;
  }

  s = ang( u );
  t = ang( v );

  if ( u == v ) while ( 1 ); 
  if ( feq( s, t ) ) while ( 1 );

  return true;
}

typedef pair<double, double> PDD;

// n^2 log n
double circle_union( P C[], double R[], int n ) {
  // will eliminate useless circle
  bool fl[N];
  CLR( fl, 1 );
  REP( i, n ) FOR( j, i + 1, n ) if ( C[i] == C[j] && feq( R[i], R[j] ) ) fl[j] = 0;
  REP( i, n ) REP( j, n ) if ( i != j && contained( C[i], R[i], C[j], R[j] ) ) fl[i] = 0;

  int nn = 0;
  REP( i, n ) if ( fl[i] ) {
    C[nn] = C[i]; R[nn] = R[i]; nn++;
  }

  n = nn;

  double A1 = 0.0, A2 = 0.0;
  REP( i, n ) {
    PDD I[N];
    int m = 0;
    REP( j, n ) if ( i != j ) {
      double s, t;
      if ( intersect( C[i], R[i], C[j], R[j], s, t ) ) {
        if ( !feq( s, t ) ) {
          if ( s > t ) {
            I[m++] = PDD( s, 2.0 * PI );
            I[m++] = PDD( 0.0, t );
          } else {
            I[m++] = PDD( s, t );
          }
        } else {
          while ( 1 );
        }
      }
    }
    sort( I, I + m );

    PDD cpl[N];
    int k = 0;
    if ( m > 0 ) {
      double cur = I[0].second;
      FOR( j, 1, m ) {
        double st = I[j].first, en = I[j].second;
        if ( st > cur + EPS ) { 
          cpl[k++] = PDD( cur, st );
        }
        cur = max( cur, en );
      }

      if ( I[0].first + 2 * PI > cur + EPS ) { 
        cpl[k++] = PDD( cur, I[0].first + 2.0 * PI );
      }
    } else {
      cpl[k++] = PDD( 0.0, 2 * PI );
    }

    REP( j, k ) {
      double s = cpl[j].first, t = cpl[j].second;
      A1 += 0.5 * SQR( R[i] ) * ( ( t - s ) - sin( t - s ) );
      P a = C[i] + P( cos(s), sin(s) ) * R[i], b = C[i] + P( cos(t), sin(t) ) * R[i] ; 
      A2 += 0.5 * ( a ^ b );
    }
  }

  A2 = fabs( A2 );

  return A1 + A2;
}


int main() {
  int n = 0;
  double coor[N];
  double R[N];
  P C[N];

  while ( 1 ) {
    int ok = 1;
    REP( i, 8 ) { 
      scanf( "%lf", &coor[i] );
      if ( coor[i] < EPS ) ok = 0;
    }
    if ( !ok ) break;
    P seg[2][2];
      REP( i, 2 ) { 
        REP( j, 2 ) {
          seg[i][j] = P( coor[i * 4 + j * 2], coor[i * 4 + j * 2 + 1]);
        }
      }
    n = 0;
    REP( i, 2 ) REP( j, 2 ) {
      C[n] = (seg[0][i] + seg[1][j] ) * 0.5;
      R[n] = (seg[0][i] - seg[1][j] ).mag() / 2.0;
      n++;
    }

    REP( i, n ) {
      C[i].out();
      printf( " %.3f\n", R[i] );
    }
    double ans = circle_union( C, R, n );
    printf( "%.3f\n", ans );
  }
  return 0;
}

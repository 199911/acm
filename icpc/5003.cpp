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
  void out() const  { printf( "(%f, %f)", x, y ); }

  P operator+( const P p ) const { return P( x + p.x, y + p.y ); }
  P operator-( const P p ) const { return P( x - p.x, y - p.y ); }
  P operator*( const double s ) const { return P( x * s, y * s ); }
  double operator*( const P p ) const { return x * p.x + y * p.y; }
  double operator^( const P p ) const { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return feq( x, p.x ) && feq( y, p.y ); }

  double mag() { return sqrt( x * x + y * y + EPS ); }
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
  return ( ( b - a ) ^ ( c - a ) ) > -EPS;
}

bool Ccw( P a, P b, P c ) {
  return ( ( b - a ) ^ ( c - a ) ) > EPS;
}

bool btw( P a, P b, P c ) {
  if ( !feq( ( b - a ) ^ ( c - a ), 0.0 ) ) return 0;
  double s = ( b - a ) * ( c - a );
  return fge( s, 0.0 ) && fle( s, ( c - a ).mag2() );
}

#define N 2222

int n, x, y, r, piv, S[N], m, cas = 1;
double R;
P p[N], C;

bool up( P a ) {
  return a.y == 0 ? a.x > 0 : a.y > 0;
}

bool comp( const int &a, const int &b ) {
  if ( a == piv || b == piv ) return b == piv;
  if ( up( p[a] - p[piv] ) ^ ( up( p[b] - p[piv] ) ) ) return up( p[a] - p[piv] );
  return ccw( p[piv], p[a], p[b] );
}

double d, l, a1, a2, ar, ans;

int main() {
  while ( scanf( "%d%d%d%d", &x, &y, &r, &n ), x || y || r || n ) {
    C = P( x, y );
    R = r;
    REP( i, n ) {
      p[i].eat();
      p[i] = p[i] - C;
      S[i] = i;
    }

    ans = 0.0;
    REP( i, n ) {
      piv = i;
      sort( S, S + n, comp );
      /*
      m = n - 1;
      int a = 0, b = 0, cnt = 1;
      while( a < m ) {
        if ( a == b ) {
          do {
            cnt++; b++; b %= m;
          } while ( b != a && ccw( p[piv], p[S[a]], p[S[b]] )); 
        } else {
          while( b != a && ccw( p[piv], p[S[a]], p[S[b]] ) ) {
            cnt++; b++; b %= m;
          }
        }
        a1 = (double)cnt / n;
        d = ( p[S[a]] - p[piv] ).nor() ^( P( 0.0, 0.0 ) - p[piv] );
        if ( d < 0.0 ) d = -d;
        l = sqrt( R * R - d * d + EPS ) ;
        ar = atan2( l, d ) * R * R - l * d;
        if ( ccw( p[piv], p[S[a]], P( 0.0, 0.0 ) ) )
          ar = PI * R * R- ar;
        a2 = ar / ( PI * R * R );
        ans = max( ans, fabs( a1 - a2 ) );
        a++; cnt--;
      }

      cnt = 1;
      REP( j, m ) if ( ( p[S[j]] - p[piv] ) * p[piv] > -EPS ) cnt++;

      a1 = (double) cnt / n;
      d = p[piv].mag(), l = sqrt( R * R - d * d + EPS ), ar = atan2( l, d ) * R * R;
      double a2 = ar / ( PI * R * R );
      ans = max( ans, fabs( a2 - a1 ) );
      */
    }

    printf( "Scenario %d: %.6f\n", cas++, ans );
  }
  return 0;
}

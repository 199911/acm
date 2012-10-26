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
#define LL long long 
#define SQR(a) ((a)*(a))

#define EPS 1e-9
#define feq(a,b) (fabs((a)-(b))<EPS)
#define fgt(a,b) ((a)>(b)+EPS)
#define fge(a,b) ((a)>(b)-EPS)
#define flt(a,b) ((a)<(b)-EPS)
#define fle(a,b) ((a)<(b)+EPS)

const double PI = atan( 1.0 ) * 4;

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
  double operator^( const P &p ) const { return x * p.y - y * p.x; }
  bool operator<( const P p ) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==( const P p ) const { return feq( x, p.x ) && feq( y, p.y ); }

  double mag() { return sqrt( x * x + y * y ); }
  double mag2() { return x * x + y * y; }

  P nor() { 
    double len = mag();
    if ( len < EPS ) return P( 0.0, 0.0 );
    return * this * ( 1.0 / len ); 
  }

  P rot() { return P( -y, x ); }
  P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
  P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

typedef pair<P,P> PPP;

bool CircleOutTangent( P a1, double r1, P a2, double r2, PPP &a, PPP &b) {
  P v = a2 - a1;
  if ( v.mag2() < SQR( r1 - r2 ) + EPS ) return false;
  double alp = acos( ( r1 - r2 ) / v.mag() );
  a.first = a1 + v.nor().rot( alp ) * r1; 
  a.second = a2 + v.nor().rot( alp ) * r2;
  b.first = a1 + v.nor().rot( -alp ) * r1;
  b.second = a2 + v.nor().rot( -alp ) * r2;
  return true;
}


bool CircleInTangent( P a1, double r1, P a2, double r2, PPP &a, PPP &b) {
  P v = a2 - a1;
  if ( v.mag2() < SQR( r1 + r2 ) + EPS ) return false;
  double alp = acos( ( r2 + r1 ) / v.mag() );
  a.first = a1 + v.nor().rot( alp ) * r1; 
  a.second = a2 + v.nor().rot( alp ) * ( - r2 );
  b.first = a1 + v.nor().rot( -alp ) * r1;
  b.second = a2 + v.nor().rot( -alp ) * ( - r2 );
  return true;
}


#define N 1111

typedef pair<P, bool> PPB;
int n, qn;
P c[N];
double r[N];
PPB q[N * 4];

double ang( P a ) {
  double ret = atan2( a.y, a.x );
  if ( ret < -EPS ) ret += 2 * PI;
  return ret;
}

bool ccw( P a, P b, P c ) {
  return (( b - a ) ^ ( c - a )) > EPS;
}

bool up( P p ) {
  return p.y == 0 ? p.x > 0 : p.y > 0;
}

  bool comp( const PPB &a, const PPB &b ) {
    if ( up( a.first ) ^ up( b.first ) ) 
      return up( a.first );
    if ( fabs( a.first ^ b.first ) < EPS ) return a.second > b.second;
    return ( a.first ^ b.first ) > EPS;
  }

int main() {
  int T;
  scanf( "%d", &T );
  for( int cas = 1; cas <= T; cas++ ) {
    scanf( "%d", &n );
    if ( n > N ) while ( 1 );
    int ans = 0;
    REP( i, n ) {
      c[i].eat(); 
      scanf( "%lf", &r[i] );
      if ( r[i] < EPS ) while ( 1 );
    }
    REP( i, n ) {
      int cur = 0, add = 0, tmp = 0;
      qn = 0;
      REP( j, n ) {
        if ( i != j ) {
          if ( ( c[j] - c[i] ).mag2() < SQR( r[i] - r[j] ) - EPS ) { 
            if ( r[i] < r[j] + EPS ) add++;
          } else if ( ( c[j] - c[i] ).mag2() < SQR( r[i] - r[j] ) + EPS ) { 
            if ( r[i] < r[j] + EPS ) add++;
            else {
              P nr = (( c[i] - c[j] ).nor() * r[i] ).rot();
              q[qn++] = PPB( nr, true ); 
              q[qn++] = PPB( nr, false ); 
            }
          } else if ( (c[j] - c[i]).mag2() < SQR( r[i] + r[j] ) + EPS ) {
            PPP a, b;
            CircleOutTangent( c[i], r[i], c[j], r[j], a, b );
            if ( !ccw( a.first, a.second, c[i] ) ) swap( a, b );
            PPB st = PPB( a.second - a.first, true ), en = PPB( b.first - b.second, false );
            if( !comp( st, en ) ) cur++;
            q[qn++] = st;
            q[qn++] = en;
          } else {
            PPP a, b, s, t;
            CircleOutTangent( c[i], r[i], c[j], r[j], a, b );
            CircleInTangent( c[i], r[i], c[j], r[j], s, t );
            if ( !ccw( a.first, a.second, c[i] ) ) swap( a, b );
            if ( !ccw( s.first, s.second, c[i] ) ) swap( s, t );
            PPB st, en;
            st = PPB( a.second - a.first, true );
            en = PPB( s.second - s.first, false );
            if ( !comp( st, en ) ) cur++;
            q[qn++] = st;
            q[qn++] = en;

            st = PPB( t.first - t.second, true );
            en = PPB( b.first - b.second, false );
            if ( !comp( st, en ) ) cur++;
            q[qn++] = st;
            q[qn++] = en;
          }
        }
      }

      sort( q, q + qn, comp );

      REP( j, qn ) {
        if ( q[j].second ) cur++;
        else cur--;
        tmp = max( tmp, cur );
      }

      tmp++;

      ans = max( ans, tmp + add );
    }

    printf( "Case #%d: %d\n", cas, ans );
  }

  return 0;
}


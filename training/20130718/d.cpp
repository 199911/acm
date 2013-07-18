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
#include <bitset>
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

struct P {
  double x, y;
  P() {}
  P( double x, double y ): x(x), y(y) {}
  void eat() { scanf( "%lf%lf", &x, &y ); }
  P operator+( P p ) { return P( x + p.x, y + p.y ); }
  P operator-( P p ) { return P( x - p.x, y - p.y ); }
  P operator*( double s ) { return P( s * x, s * y ); }
  double operator*( P p ) { return x * p.x + y * p.y; }
  double operator^( P p ) { return x * p.y - y * p.x; }
  double mag() { return sqrt( x * x + y * y ); }
}; 

#define EPS 1e-9
#define N 33

int n, cx[2], cy[2]; 
P p[N][2], t;
double x[2][33], y[2][33];

bool Ccw( P a, P b, P c ){
  return ( ( b - a ) ^ ( c - a ) ) > EPS;
}

int count( P a, P b ) {
  int cnt = 0;
  REP( i, n ) {
    if ( Ccw( p[i][0], p[i][1], a ) != Ccw( p[i][0], p[i][1], b ) ) cnt++; 
  }
  return cnt;
}

int main() {
  scanf( "%d", &n );
  REP( i, n ) REP( j, 2 ) p[i][j].eat();
  cx[0] = cx[1] = cy[0] = cy[1] = 0;
  REP( c, 2 ) { 
    x[c][cx[c]++] = 0;
    x[c][cx[c]++] = 100;

    y[c][cy[c]++] = 0;
    y[c][cy[c]++] = 100;
  }
  REP( i, n ) REP( j, 2 ) {
    if ( fabs( p[i][j].x ) < EPS ) x[0][cx[0]++] = p[i][j].y;
    if ( fabs( p[i][j].y ) < EPS ) y[0][cy[0]++] = p[i][j].x;
    if ( fabs( p[i][j].x - 100 ) < EPS ) x[1][cx[1]++] = p[i][j].y;
    if ( fabs( p[i][j].y - 100 ) < EPS ) y[1][cy[1]++] = p[i][j].x;
  }
  t.eat();
  
  REP( c, 2 ) {
    sort( x[c], x[c] + cx[c] ); 
    sort( y[c], y[c] + cy[c] ); 
  }

  int ans = n;
  REP( c, 2 ) {
    REP( i, cx[c] - 1 ) {
      P bg = P( c * 100.0, ( x[c][i] + x[c][i + 1] ) / 2.0 );
      ans = min( ans, count( bg, t ) );
    }

    REP( i, cy[c] - 1 ) {
      P bg = P( ( y[c][i] + y[c][i + 1] ) / 2.0, c * 100 ); 
      ans = min( ans, count( bg, t ) );
    }
  }
  printf( "Number of doors = %d\n", ans + 1);
  return 0;
}

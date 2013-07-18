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
#define N 22

bool Ccw( P a, P b, P c ) {
  return (( b - a ) ^ ( c - a )) > EPS;
}

bool btw( P a, P b, P c ) {
  return fabs( ( a - b ).mag() + ( b - c ).mag() - ( a - c ).mag() ) < EPS;
}

bool ssi( P a, P b, P c,  P d ) {
  if ( btw( a, c, b ) || btw( a, c, b ) || btw( c, a, d ) || btw( c, b , d ) ) return true;
  return Ccw( a, b, c ) != Ccw( a, b, d ) && Ccw( c, d, a ) != Ccw( c, d, b );
}

int adj[N][N], n;
P a[22][2];

int main() {
  while ( scanf( "%d", &n ), n ) {
    REP( i, n ) 
      REP( j, 2 ) 
      a[i][j].eat();
    CLR( adj, 0 );
    REP( i, n ) REP( j, n ) if( ssi( a[i][0], a[i][1], a[j][0], a[j][1] ) ) adj[i][j] = adj[j][i] = 1;

    REP( i, n ) REP( j, n ) REP( k, n ) adj[j][k] |= adj[j][i] && adj[i][k];

    int a, b;
    while( scanf( "%d%d", &a, &b ), a || b ) {
      a--; b--;
      printf( "%s\n", adj[a][b] ? "CONNECTED" : "NOT CONNECTED" );
    }
  }
  return 0;
}

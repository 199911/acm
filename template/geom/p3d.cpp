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
  double x, y, z;
  P() {}
  P( double x, double y, double z ): x(x), y(y), z(z) {}
  void eat() { scanf( "%lf%lf%lf", &x, &y, &z ); }
  void out() { printf( " (%.3f, %.3f, %.3f) " ); }

  P operator+( P p ) { return P( x + p.x, y + p.y, z + p.z); }
  P operator-( P p ) { return P( x - p.x, y - p.y, z - p.z); }
  P operator*( double s ) { return P( x * s, y * s, z * s); }
  double operator*( P p ) { return x * p.x + y * p.y + z * p.z; }
  P operator^( P p ) { return P( y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }

  double mag2() { return x * x + y * y + z * z; }
  double mag() { return sqrt( x * x + y * y + z * z ); }

  P nor() { return *this * ( 1.0 / mag() ); }
};

int main() {

  return 0;
}

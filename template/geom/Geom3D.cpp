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
	double x, y, z;
	P() {}
	P( double x, double y, double z ) : x(x), y(y), z(z) {}
	void eat() { scanf( "%lf%lf%lf", &x, &y, &z ); }
	void out() { printf( "( %3.f, %3.f, %.3f ) ", x, y, z ); }

	P operator+( P p ) { return P( x + p.x, y + p.y, z + p.z ); }
	P operator-( P p ) { return P( x - p.x, y - p.y, z - p.z ); }
	P operator*( double s )  { return P( x * s, y * s, z * s ); }
	double operator*( P p ) { return x * p.x + y * p.y + z * p.z; }
	P operator^( P p ) { return P( y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); } 

	double mag() { return sqrt( x * x + y * y + z * z ); }
	double mag2() { return x * x + y * y + z * z; }

	P nor() { return * this * ( 1.0 / mag() ); }
};

// plane-plane intersection
// assume plane is given by n * x = h
bool ppi( P n1, double h1, P n2, double h2, P &r1, P &r2 ) {
	if ( ( n1 ^ n2 ).mag() < EPS ) return false;
	P nr = n1 ^ n2;
	double c1 = ( h1 - n1 * n2 * h2 ) / ( 1 - ( n1 * n2 ) * ( n1 * n2 ) ), c2 = ( h2 - n1 * n2 * h1 ) / ( 1 - ( n1 * n2 ) * ( n1 * n2 ) );
	r1 = n1 * c1 + n2 * c2;
	r2 = r1 + nr.nor();
	return true;
}

int main() {
	return 0;
}

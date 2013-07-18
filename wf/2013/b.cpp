#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long

double p, x;

double calc( int a, int b ) {
	double nu = 1.0 - pow( p / ( 1 - p ), a ), de = 1.0 - pow( p / ( 1 - p ), a + b );
	double Pl = nu / de;
	double ret = a * (1 - Pl) - b * ( 1 - x ) * Pl; 
//	printf( "%d %d => %f %f %f\n", a, b, 1 - Pl, Pl, ret );
	return ret;
}

#define MAX 100000

double searchB( int a ) {
	int lo = 0, hi = MAX;
	while( lo < hi - 1 ) {
		int t = ( hi - lo ) / 3;
		if ( !t ) break;
		int t1 = lo + t , t2 = hi - t;
		if ( calc( a, t1 ) > calc( a, t2 ) ) hi = t2;
		else lo = t1;
	}
	double ret = -1e10;
	for( int i = lo; i <= hi; i++ ) 
		ret = max( ret, calc( a, i ) );
	return ret;
}

double searchA( ) {
	double ret = -1e10;
	for( int a = 0; a <= MAX; a++ ) 
		ret = max( ret, searchB( a ) );
	return ret;
}

int main() {
	scanf( "%lf%lf", &x, &p );
	x /= 100; p /= 100;
	printf( "%f\n", searchA() );
  return 0;
}

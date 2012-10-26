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

#define EPS 1e-9

struct P {
  double x, y, z;
  P() {}
  P( double x, double y, double z ): x(x), y(y), z(z) {}
  void eat() { scanf( "%lf%lf%lf", &x, &y, &z ); }
  void out() { printf( "(%.2f %.2f %.2f) ", x, y, z ); }

  P operator+( P p ) { return P( x + p.x, y + p.y, z + p.z); }
  P operator-( P p ) { return P( x - p.x, y - p.y, z - p.z); }
  P operator*( double s ) { return P( x * s, y * s, z * s); }
  double operator*( P p ) { return x * p.x + y * p.y + z * p.z; }
  P operator^( P p ) { return P( y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }

  double mag2() { return x * x + y * y + z * z; }
  double mag() { return sqrt( x * x + y * y + z * z ); }

  P nor() { return *this * ( 1.0 / mag() ); }
};

#define N 500 

P A[N];
int n;

struct F {
	int a, b, c;
	F() {}
	F( int a, int b, int c ):a(a), b(b), c(c) {} 
	
	P nor() { return ( A[b] - A[a] ) ^ ( A[c] - A[a] ); }
	P mid() { return ( A[a] + A[b] + A[c] ) * ( 1.0 / 3.0 ); }
	bool vis( P p ) {
		return ( p - mid() ) * nor() > EPS;
	}
};

F fl[N * N];
int hd, nt[N * N], rm[N * N], en;
int ed[N][N];

void init() {
	hd = -1;
	en = 0;
}

void add_face( int a, int b, int c ) {
	fl[en] = F( a, b, c );
	rm[en] = 0;
	nt[en] = hd;
	hd = en++;
}

bool hull3d() {
	if ( n <= 3 ) return false;

	init();
	bool fail = 1;
	for( int i = 2; i < n; i++ ) 
		if ( (( A[1] - A[0] ) ^ ( A[i] - A[0] ) ).mag() > EPS ) { 
			swap( A[i], A[2] ); fail = 0; break; 
		}
	if ( fail ) return false;

	fail = 1;
	P nr = ( A[1] - A[0] ) ^ ( A[2] - A[0] );
	for( int i = 3; i < n; i++ ) {
		if ( fabs( nr * ( A[i] - A[0] ) ) > EPS ) {
			swap( A[i], A[3] );
			fail = 0;
			break;
		}
	}
	if ( fail ) return false; 

	if ( ( ( A[1] - A[0] ) ^ ( A[2] - A[0] ) ) * ( A[3] - A[0] ) > EPS  ) 
		swap( A[1], A[0] );

	add_face( 0, 1, 2 ); add_face( 3, 1, 0 ); add_face( 3, 2, 1 ); add_face( 3, 0, 2 );
	
	memset( ed, 0, sizeof(ed) );
	memset( rm, 0, sizeof(rm) );

	for( int i = 4; i < n; i++ ) {
		for( int pt = hd; pt != -1; pt = nt[pt] ) {
			if ( fl[pt].vis( A[i] ) ) { // visible
				F f = fl[pt];
				rm[pt] = 1;
				ed[f.a][f.b] = ed[f.b][f.c] = ed[f.c][f.a] = i;
			}
		}

		for( int pt = hd; pt != -1; pt = nt[pt] ) {
			if ( rm[pt] ) {
				F f = fl[pt];
				if ( ed[f.b][f.a] != i ) add_face( i, f.a, f.b ); 
				if ( ed[f.c][f.b] != i ) add_face( i, f.b, f.c ); 
				if ( ed[f.a][f.c] != i ) add_face( i, f.c, f.a ); 
			}
		}

		for( int pt = hd, lt = hd; pt != -1; pt = nt[pt] ) {
			if ( rm[pt] ) 
				if ( pt == hd ) hd = nt[pt];
				else nt[lt] = nt[pt];
			else lt = pt;
		}
	}

	return true;
}

int main() {
	int cas = 1;
	while( scanf( "%d", &n ) != EOF ) {
		for( int i = 0; i < n; i++ ) 
			A[i].eat();
		hull3d();
		int ans = 0;
		for( int pt = hd; pt != -1; pt = nt[pt] ) {
			int ok = 1;
			for( int qt = nt[pt]; ok && qt != -1; qt = nt[qt] ) {
				double crs = ( fl[pt].nor() ^ fl[qt].nor() ).mag();
				double dot = fl[pt].nor() * fl[qt].nor(); 
				if ( fabs( crs ) < EPS && dot > EPS ) ok = 0;
			}
			ans += ok;

		}
		printf( "%d\n", ans );
	}
  return 0;
}

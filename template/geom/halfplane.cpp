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

#define EPS 1e-9
#define feq(a,b) (fabs((a)-(b))<EPS)
#define fgt(a,b) ((a)>(b)+EPS)
#define fge(a,b) ((a)>(b)-EPS)
#define flt(a,b) ((a)<(b)-EPS)
#define fle(a,b) ((a)<(b)+EPS)

struct P {
	double x, y;
	P() {}
	P( double x, double y ): x(x), y(y) {}
	int eat() { return scanf( "%lf%lf", &x, &y ); }
	void out() { printf( "(%f, %f)", x, y ); }

	P operator+( P p ) { return P( x + p.x, y + p.y ); }
	P operator-( P p ) { return P( x - p.x, y - p.y ); }
	P operator*( double s ) { return P( x * s, y * s ); }
	double operator*( P p ) { return x * p.x + y * p.y; }
	double operator^( P p ) { return x * p.y - y * p.x; }

	double mag() { return sqrt( x * x + y * y ); }
	double mag2() { return x * x + y * y; }

	P nor() { return * this * ( 1.0 / mag() ); }

	P rot() { return P( -y, x ); }
	P rot( double si, double co ) { return P( x * co - y * si, x * si + y * co ); }
	P rot( double th ) { return rot( sin( th ), cos( th ) ); }
};

double area(P a, P b, P c) {
	return 0.5 * ( ( b - a ) ^ ( c - a ) );
}

bool ccw(P a, P b, P c) {
  return area(a, b, c) > EPS;
}

bool btw( P a, P b, P c ) {
	return feq( ( b - a ).mag() + ( c - b ).mag(), ( a - c ).mag() );
}


bool lli( P a, P b, P c, P d, P &res ) {
//  printf("lli ");
//  a.out(), b.out(), c.out(), d.out();
//  puts("");
	if( feq( ( b - a ) ^ ( d - c ), 0.0 ) ) return false;
	res = a + ( b - a ) * ( area( c, d, a )  / ( area( c, d, a ) - area(c, d, b) ) );
	return true;
}

bool ssi(P a, P b, P c, P d, P &res) {
  if( !lli(a, b, c, d, res) ) {
    return false;
  } else {
    if( btw(a, res, b) && btw(c, res, d) ) {
      return true;
    } else {
      return false;
    }
  }
}

bool lsi(P a, P b, P c, P d, P &res){
  if(!lli(a, b, c, d, res)) {
    return false;
  } else {
    if( btw(c, res, d) ) {
      return true;
    } else {
      return false;
    }
  }
}

#define N 5000

P res[N];
int sz;

void init() {
  res[0] = P(-10000, -10000);
  res[1] = P(10000, -10000);
  res[2] = P(10000, 10000);
  res[3] = P(-10000, 10000);
  sz = 4;
}

void hpi(P a, P b) {
   int _sz = 0;
   P cur[N], e;

   REP(i, sz) {
     if( ccw(a, b, res[i]) ) {
       cur[_sz++] = res[i];
     }
     if( lsi(a, b, res[i], res[(i+1)%sz], e) ) {
       cur[_sz++] = e;
     } 
   }

   REP(i, _sz) {
     res[i] = cur[i];
   }
   sz = _sz;
}

int main() {
  P a, b;
  int m;

  scanf("%d", &m);

  while( m-- ) {
    a.eat(); b.eat();
    hpi(res, sz, a, b);
  }

  REP(i, sz) {
    res[i].out();
    puts("");
  }

	return 0;
}

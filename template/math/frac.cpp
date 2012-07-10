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

int gcd( int a, int b ) { return b ? gcd( b, a % b ) : a ; } 

struct Frac {
  int n, d;
  Frac() {}
  Frac(int n, int d): n(n), d(d) {}

  Frac sim() { 
    int g = gcd( n, d ); 
    return Frac( n / g, d / g );
  }

  // operators
  Frac operator+( Frac f ) { return Frac( n * f.d + f.n * d, d * f.d ).sim(); } 
  Frac operator+( int x ) { return * this + Frac(x, 1); }
  Frac operator-( Frac f ) { return Frac( n * f.d - f.n * d, d * f.d ).sim(); }
  Frac operator-( int x ) { return * this - Frac(x , 1); }
  Frac operator*( Frac f ) { return Frac( n * f.n, d * f.d ); }
  Frac operator*( int x ) { return Frac( n * x, d ).sim(); }
  Frac inv() { return Frac( d, n ); }
  Frac operator/( Frac f ) { return ( * this * f.inv() ).sim(); }
  Frac operator/( int x ) { return Frac( n, d * x ).sim(); }

  // relations
  bool operator<( const Frac f ) const { return n * f.d < d * f.n; }
  bool operator<=( const Frac f ) const { return n * f.d <= d * f.n; } 
  bool operator>( const Frac f ) const { return n * f.d > d * f.n; }
  bool operator>=( const Frac f ) const { return n * f.d >= d * f.n; } 
  bool operator==( const Frac f ) const { return n * f.d == d * f.n; } 
  bool operator!=( const Frac f ) const { return n * f.d != d * f.n; } 
};

int main() {
	return 0;
}

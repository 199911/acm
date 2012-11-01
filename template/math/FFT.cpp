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
#include <complex>
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

typedef complex<double> CPX;

const double PI = atan( 1.0 ) * 4;

#define N 222222
void FFT( CPX x[], int n, CPX y[], int bInv ) {
  for( int i = 0; i < n; i++ ) 
    y[i] = x[i];

  if ( n == 1 ) return;

  CPX w( 1, 0 ), wn;
  for( int i = 0; i < n; i++ ) {
    int t = i, k = 0;
    for( int j = 1; j < n; j <<= 1, t >>= 1 )
      k = ( k << 1 ) | ( t & 1 );

    if ( k < i ) swap( y[i], y[k] );
  }

  for( int t = 1; t < n; t <<= 1 ) {
    int s = 0, e = s + t;
    while( s < n ) {
      CPX a, b;
      w = CPX( 1, 0 );
      wn = CPX( cos( bInv * PI / t ), sin( bInv * PI / t ) );

      for( int j = s; j < s + t; j++ ) {
        a = y[j];
        b = y[j + t] * w;
        y[j] = a + b;
        y[j + t] = a - b;
        w = w * wn;
      }

      s = e + t;
      e = s + t;
    }
  }
}

CPX x[N], ya[N], yb[N], yc[N];

void PolyMult( double a[], int na, double b[], int nb, double c[], int &nc ) {
  int n = 1; 
  while( n < na + nb  ) n <<= 1;

  for( int i = 0; i < n; i++ ) x[i] = i < na ? a[i] : 0;
  FFT( x, n, ya, 1 );
  for( int i = 0; i < n; i++ ) x[i] = i < nb ? b[i] : 0;
  FFT( x, n, yb, 1 );

  for( int i = 0; i <n; i++ ) yc[i] = ya[i] * yb[i];
  FFT( yc, n, x, -1 );

  for( int i = 0; i < n; i++ ) 
    c[i] = x[i].real() / n;

  for( nc = n; nc > 0 && fabs( c[nc - 1] ) < 1e-9; nc-- );
}


char s[N];
int na, nb, nc;
double a[N], b[N], c[N];
int C[N];

int main() {

  while( scanf( "%s", s ) != EOF ) {
    na = strlen( s );
    REP( i, na ) a[i] = s[na - 1 - i] - '0';

    scanf( "%s", s );
    nb = strlen( s );
    REP( i, nb ) b[i] = s[nb - i - 1] - '0';


    PolyMult( a, na, b, nb, c, nc );

    memset( C, 0, sizeof( C ) );
    for( int i = 0; i < nc; i++ ) C[i] = round( c[i] );

    while( nc > 0 && C[nc - 1] == 0 ) nc--;

    for( int i = 0; i < nc; i++ ) {
      if ( C[i] >= 10 ) {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
        if ( i + 1 == nc ) nc++;
      }
    }


    if ( nc > 0 ) {
      for( int i = nc - 1; i >= 0; i-- ) {
        printf( "%d", C[i] );
      }
      puts( "" );
    } else {
      puts( "0" );
    }

  }

  return 0;
}

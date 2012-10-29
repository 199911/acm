#include <cstdio>
#include <ccomplex>
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

#define CPX complex<double>

const double PI = atan( 1.0 ) * 4;

void fft( CPX *x, int n, CPX *y, int bInv ) {
  if ( n == 1 ) { 
    y[0] = x[0];
  } else {
    CPX * xeven = new CPX[n / 2], * xodd = new CPX[n / 2], w( 1, 0 );
    CPX * yeven = new CPX[n / 2], * yodd = new CPX[n / 2], wn;

    if ( bInv ) wn = CPX( cos( - 2 * PI / n ), sin( - 2 * PI / n ) );
    else wn = CPX( cos( 2 * PI / n ), sin( 2 * PI / n ) );

    for( int i = 0; i < n / 2; i++ ) {
      xeven[i] = x[i * 2];
      xodd[i] = x[i * 2 + 1];
    }

    fft( xeven, n / 2, yeven, bInv );
    fft( xodd, n / 2, yodd, bInv );

    for( int i = 0; i < n / 2; i++ ) {
      y[i] = yeven[i] + w * yodd[i];
      y[i + n / 2] = yeven[i] - w * yodd[i];
      w *= wn;
    }

    delete xeven;
    delete xodd;
    delete yeven;
    delete xodd;
  }
}

int main() {
  return 0;
}

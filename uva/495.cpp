#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
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

const int MAXDIGIT = 9999;

#define N 1111

struct MP {
  int d[N], n, ofl;
  MP(): n(0), ofl(0) { memset(d, 0, sizeof(d)); }
  MP(int x): n(0), ofl(0) {
    memset(d, 0, sizeof(d));
    while( x ) {
      d[n++] = x % 10;
			x /= 10;
    }
    if ( n == 0 ) n = 1;
  }
  void eat() {
    char str[N];
    scanf( "%s", str );
    n = strlen(str);
    for( int i = 0; i < n; i++ ) d[i] = str[n - i - 1] - '0';
  }

  int operator[] (int k) { return k < n ? d[k] : 0; }

  MP operator+( MP a ) {
    MP ret;
    int m = max(n, a.n);

    for( int i = 0; i < m; i++ ) 
      ret.d[i] = d[i] + a.d[i];

    for( int i = 0; i < m; i++ ) {
      ret.d[i+1] += ret.d[i] / 10;
      ret.d[i] %= 10;
    }

    if ( ret.d[m] ) m++;

    if ( m > MAXDIGIT ) ofl = 1;

    ret.n = m;
    
    return ret;
  }

  MP operator*( MP a ) {
    MP ret;
    if ( a.ofl || ofl || n + a.n - 1 > MAXDIGIT ) {
      ret.ofl = 1; return ret;
    }
    for ( int i = 0; i < n; i++ ) 
      for ( int j = 0; j < a.n; j++ ) 
        ret.d[i+j] += d[i] * a.d[j];
    for ( int i = 0; i < n + a.n; i++ ) {
      ret.d[i+1] += ret.d[i] / 10;
      ret.d[i] %= 10;
    }
    if ( ret.d[n + a.n - 1] ) ret.n = n + a.n;
    else ret.n = n + a.n - 1;

    if ( ret.n > MAXDIGIT ) ret.ofl = 1;
    return ret;
  }

  void out() { for ( int i = n - 1; i >= 0; i-- ) printf("%d", d[i]); }
};


// multiply 2 * 2 matrices
void mul( MP a[2][2], MP b[2][2], MP c[2][2] ) {
	REP( i, 2 ) REP( j, 2 ) {
		c[i][j] = MP(0);
		REP( k , 2 ) c[i][j] = c[i][j] + a[i][k] * b[k][j];
	}
}

MP fib( int k ) {
	MP cur[2][2] = { {MP(1), MP(1)}, {MP(1), MP(0)}}, res[2][2] = {{MP(1), MP(0)}, {MP(0), MP(1)}}, tmp[2][2];
	while ( k ) {
		if ( k & 1 ) {
			mul( res, cur, tmp );
			REP(i, 2) REP(j, 2) res[i][j] = tmp[i][j];
		}

		mul( cur, cur, tmp );
		REP( i, 2 ) REP(j, 2) cur[i][j] = tmp[i][j];

		k >>= 1;
	}

	return res[0][1];
}

int main() {
	int n;
	while ( cin >> n ) {
		MP res= fib( n );
		printf( "The Fibonacci number for %d is ", n);
		res.out();
		puts( "" );
	}
  return 0;
}

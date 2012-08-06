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

#define N 4444

int MOD;

void tobit( LL x, int d[], int &n ) {
	n = 0;
	while ( x ) {
		d[n++] = x % 2;
		x >>= 1;
	}
}


// multiply 2 * 2 matrices
void mul( int a[2][2], int b[2][2], int c[2][2] ) {
	REP( i, 2 ) REP( j, 2 ) {
		c[i][j] = 0;
		REP( k , 2 ) { 
			c[i][j] += a[i][k] * b[k][j];
			c[i][j] %= MOD;
		}
	}
}

void exp( int a[2][2], int b[], int n, int res[2][2] ) {
	int tmp[2][2];
	REP( i, 2 ) REP( j, 2 ) res[i][j] = i == j;
	REP( i, n ) {
		if ( b[i] & 1LL ) {
			mul( res, a, tmp );
			REP( i, 2 ) REP( j, 2 ) res[i][j] = tmp[i][j];
		}
		mul(a, a, tmp);
		REP(i, 2) REP( j, 2 ) a[i][j] = tmp[i][j];
	}
}

int fib( LL a, LL b ) {
	int res[2][2] = { {1, 1}, {1, 0} }, tmp[2][2];

	return res[0][1];
}

int main() {
	LL a, b, T;
	cin >> T;
	while ( T-- ) {
		cin >> a >> b >> MOD;
		int res= fib( a, b );
		printf( "%d\n", res );
	}
  return 0;
}

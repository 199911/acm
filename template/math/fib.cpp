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

// multiply 2 * 2 matrices
void mul( LL a[2][2], LL b[2][2], LL c[2][2] ) {
	REP( i, 2 ) REP( j, 2 ) {
		c[i][j] = 0;
		REP( k , 2 ) c[i][j] = c[i][j] + a[i][k] * b[k][j];
	}
}

LL fib( LL k ) {
	LL cur[2][2] = { {1, 1}, {1, 0}}, res[2][2] = {{1, 0}, {0, 1}}, tmp[2][2];
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
		LL res= fib( n );
		printf( "%lld\n", res );
	}
  return 0;
}

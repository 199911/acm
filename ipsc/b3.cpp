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
#include <bitset>
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

#define N 1111111

LL memo[N];

LL f( LL n ) {
	if ( n < N && memo[n] != -1 ) {
		return memo[n];
	} else if ( n == 1 ) {
		return memo[1] = 0;
	}

	LL ans = 0;

	LL k = sqrt( n + 1e-9 );
	LL x = n / k, y = n - x;
	LL a = n / ( k + 1 ), b = n - a;

	if ( x && y ) ans = max( ans, f(x) + f(y) + x * y ) ;
	if ( a && b ) ans = max( ans, f(a) + f(b) + a * b );

	if ( n < N )  memo[n] = ans;
	return ans;
}

int main() {
	LL n;
	int T;
	scanf( "%d", &T );
	CLR( memo, - 1 );
	memo[1] = 0;
	while( T-- ) {
		scanf( "%lld", &n );
		printf( "%lld\n", f(n) );
	}
  return 0;
}

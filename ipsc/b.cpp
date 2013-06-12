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

LL memo[1111111];

LL f( LL n ) {
	LL x, y;

	if( memo[n] != -1 ) return memo[n];
	if ( n == 1 ) return memo[1] = 0;

	if ( n % 3 == 0 ) {
		x = n / 3;
		y = n - x;
	} else if ( n % 2 == 0 ) {
		x = y = n / 2;
	} else {
		x = n - 1;
		y = 1;
	}
	return memo[n] = x * y + f( x ) + f( y );
}

int main() {
	int T;
	LL n;
	scanf( "%d", &T );
	memset( memo, -1, sizeof( memo ) );
	while( T-- ) {
		scanf( "%lld", &n );
		printf( "%lld\n", f(n) );
	}
  return 0;
}

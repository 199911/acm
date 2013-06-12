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

map<LL, LL> memo;

LL f( LL n ) {
	if ( memo.find(n) != memo.end() ) {
		return memo[n];
	} else if ( n == 1 ) {
		return memo[1] = 0;
	}

	LL x = n / 2, y = n - n / 2;

	return memo[n] = f(x) + f(y) + x * y;
}

int main() {
	LL n;
	int T;
	scanf( "%d", &T );
	memo.clear();
	memo[1] = 0;
	while( T-- ) {
		scanf( "%lld", &n );
		printf( "%lld\n", f(n) );
	}
  return 0;
}

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

// guarantee 
bool doit( LL rnk, LL n, LL ply ) {
	//printf( "%lld %lld %lld\n", rnk, n, ply );
	if ( rnk < ( n / 2 )  ) {
		return ply == 0;
	} else {
		return doit ( rnk - n / 2, n / 2, ( ply - 1 ) / 2 );
	}
}

bool doit2( LL rnk, LL n, LL ply ) {
	if ( rnk >= n / 2 - 1 ) {
		return ply < n - 1;
	} else {
		LL bk = ( n - 1 - ply - 1 ) / 2;
		return doit2( rnk, n / 2, n / 2 - 1 - bk );
	}
}

LL f1( LL n, LL p ) {
	if ( p == n - 1 ) return n - 1;
	LL lo = 0, up = n - 1;
	while( lo + 1 < up ) {
		LL mid = ( lo + up ) / 2;
		if ( doit ( p, n, mid ) ) {
			lo = mid;
		} else {
			up = mid;
		}
	}
	return lo;
}

LL f2( LL n, LL p ) {
	if ( p == n - 1 ) return n - 1;
	LL lo = 0, up = n - 1;
	while( lo + 1 < up ) {
		LL mid = ( lo + up ) / 2;
		if ( doit2( p, n, mid ) ) {
			lo = mid;
		} else {
			up = mid;
		}
	}
	return lo;
}

int main() {
	int T;
	scanf( "%d", &T );
	REP( cas, T ) {
		LL n, p;
		scanf( "%lld%lld", &n, &p );
		n = 1ll << n;
		p--;
		printf( "Case #%d: %lld %lld\n", cas + 1, f1( n, p ), f2( n, p ) ); 
	}
  return 0;
}

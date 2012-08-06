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

#define N 111111111 

LL f[11111];
int fn = 0;


int main() {
	f[0] = 0;
	f[1] = 1;
	for ( fn = 2; (f[fn] = f[fn - 1] + f[fn - 2]) <= N; fn++ );

	LL n;
	int t;

	cin >> t;

	while ( t-- ) {
		cin >> n;

		int p = fn - 1;
		while ( f[p] > n ) p--;

		printf( "%lld = ", n );

		for ( int i = p; i > 1; i-- ) {
			printf( "%d", n >= f[i] ? 1 : 0 );
			if ( n >= f[i] ) n -= f[i];
		}

		puts( " (fib)" );

	}
  return 0;
}

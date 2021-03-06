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

#define N 222222

int bk[N], fs[N], fi[N], mt[333], n, m;
char s[N], t[N];

int main() {
	scanf( "%s%s", s, t );
	n = strlen( s );
	m = strlen( t );

	CLR( bk, 0 );
	CLR( fs, -1 );
	CLR( mt, -1 );

	for( int i = 0, p = 0; i < n; i++ ) {
		if ( p < m && s[i] == t[p] ) mt[s[i]] = p++;
		fs[i] = mt[s[i]];
	}

	for( int i = n - 1, p = 0; i >= 0; i-- ) {
		if ( p < m && s[i] == t[m - 1 - p] ) p++;
		bk[i] = p;
	}

	int ok = 1;

	for( int i = 0; i < n; i++ ) {
		if ( fs[i] < 0 ) ok = 0; 
		else if ( fs[i] + bk[i] < m ) ok = 0;
	}

	printf( "%s\n", ok ? "YES" : "NO" );

	return 0;
}

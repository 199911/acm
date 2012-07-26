#include <cstdio>
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
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define SQR(a) ((a)*(a))
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

#define N (1<<17)

int p[N], pn;
bool ip[N];

void seive( int n ) {
	pn = 0;
	CLR(ip,1);
	FOR(i, 2, n) {
		if ( ip[i] ) {
			p[pn++] = i;
			for( int j = i + i; j <= n; j += i ) ip[j] = 0;
		}
	}
}

void factorize(LL k, int pf[], int pe[], int &r) {
	r = 0;
	LL res = k;

	for ( int i = 0; res > 1 && i < pn && SQR(p[i]) <= k; i++ ) {
		if ( res % p[i] == 0 ) {
			pf[r] = p[i];
			pe[r] = 0;
			while( res % p[i] == 0 ) {
				res /= p[i];
				pe[r]++;
			}
			r++;
		}
	}

	if ( res > 1 ) {
		pf[r] = res;
		pe[r++] = 1;
	}
}

int phi( int x ) {
	int pf[N], pe[N], r;
	factorize( x, pf, pe, r );
	REP(i, r) {
		x = x / pf[i] * (pf[i] - 1);
	}
	return x;
}

int main() {
	seive( 1 << 16 );
	int x;
	while( cin >> x && x ) {
		printf("%d\n", phi(x));
	}
	return 0;
}

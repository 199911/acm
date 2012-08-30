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

LL count( LL k ) {
	LL tmp = k;
	LL cnt = 0;
	int cb = 0;
	while ( tmp ) {
		cb++; tmp >>= 1;
	} 

	for ( int p = 1; p < cb; p++ ) {
		LL c, tmp = 0, s, t;

		if ( cb % p == 0 ) {
			s = k;
			while ( s >> p ) s >>= p;
			s -= 1 << (p - 1);
			s++;

			tmp += s;

		}

		if ( cb / p > 2 ) {
			tmp += ( cb / p - 2 ) * ( (1 << (p - 1)));
		}


		c = 1;

		for ( int i = p + p; i < cb; i += p )  c--;

		cnt += tmp * c;
	}

	return cnt;
}

int main() {
	LL l, r;

	cin >> l >> r;
	cout << count(r) - count( l - 1 ) << endl;
  return 0;
}

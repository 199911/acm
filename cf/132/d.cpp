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

int main() {
	LL n, m;
	LL t[111111], T[111111], c[111111], x[111111];

	cin >> n >> m;

	REP( i, n ) {
		cin >> t[i] >> T[i] >> x[i] >> c[i];
	}

	LL ans = 0;
	REP( i, n ) {
		LL cap = T[i] - t[i];
		LL tmp;

		if ( cap > 0 ) {
			LL ca = m / cap + ( m % cap ? 1 : 0);
			LL tmp1 = ca * c[i];
			LL cb = m / cap;
			LL tmp2 = cb * c[i] + ( m % cap ? m % cap + cap: 0 ) * x[i];
			LL tmp3 = c[i] + x[i] * m;
			tmp = min(tmp1, min(tmp2, tmp3)); 
		} else {
			tmp = m * x[i] + c[i];
		}

		ans += tmp;
	}
	cout << ans << endl;
	return 0;
}

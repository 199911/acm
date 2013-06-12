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

struct F {
	LL a, b;
	F() {}
	F( LL a, LL b ): a(a), b(b) {}
	LL gcd( LL x, LL y ) { return y ? gcd( y, x % y ) : x; }
	F reduce() { LL r = gcd( a, b ); a /= r;  b /= r; return *this; }
	F operator+( F f ) { return F( a * f.b + b * f.a, b * f.b ).reduce(); }
	F operator-( F f ) { return F( a * f.b - b * f.a, b * f.b ).reduce(); }
	bool operator<( F f ) const { return a * f.b - b * f.a < 0; }
};

void rational_approx( F t, F &l, F &u, LL MD ) {
	l = F( 0, 1 );
	u = F( 1, 0 );
	while( 1 ) {
		F mid = F( l.a + u.a, l.b + u.b );
		if ( mid.b > MD ) break;
		if ( t < mid ) {
			u = mid;
		} else if ( mid < t ) {
			l = mid;
		} else {
			u = l = mid;
			break;
		}
	}
}

int main() {
	LL x, y, n;
	F u, l, t, ans;
	cin >> x >> y >> n;
	t = F( x, y );
	rational_approx( t, l, u, n );
	if ( t - l < u - t ) {
		ans = l;
	} else if ( u - t < t - l ) {
		ans = u;
	} else {
		if ( l.b == u.b ) {
			ans = l;
		} else {
			ans = l.b < u.b ? l : u;
		}
	}
	cout << ans.a << "/" << ans.b << endl;
  return 0;
}

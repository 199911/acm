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

int prime[] = { 1000003, 1388029, 1424939, 1464289, 1579043, 1637549, 1722649, 1854763, 1963513 }, pn = 9;

#define get_digit(k) ((k) - (isdigit(k) ? '0' : 'A' - 10))

int conv( string str, int base, int mod ) {
	int ret = 0;
	for ( int i = 0; i < str.length() ; i++ ) {
		int tmp = get_digit(str[i]);
		ret *= base;
		ret %= mod;
		ret += tmp;
		ret %= mod;
	}

	return ret;
}


int main() {
	string s1, s2;

	while ( cin >> s1 >> s2 ) {
		int mb1 = 2, mb2 = 2, bb1 = -1, bb2 = -1;
		REP(i, s1.length()) gmax(mb1, get_digit(s1[i]) + 1);
		REP(i, s2.length()) gmax(mb2, get_digit(s2[i]) + 1);

		FOE(bs1, mb1, 36) {
			FOE(bs2, mb2, 36 ) {
				int ok = 1;
				REP(p, pn) {
					int x1 = conv(s1, bs1, prime[p]);
					int x2 = conv(s2, bs2, prime[p]);
					if ( x1 != x2 ) ok = 0;
				}
				if ( ok ) {
					bb1 = bs1; bb2 = bs2;
					goto end;
				}
			}
		}

end:
		if ( bb1 != -1 && bb2 != -1 ) 
			printf("%s (base %d) = %s (base %d)\n", s1.c_str(), bb1, s2.c_str(), bb2);
		else 
			printf("%s is not equal to %s in any base 2..36\n", s1.c_str(), s2.c_str());
	}
  return 0;
}

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

string str;
int ans, n, s[1111111];

int main() {
	cin >> str;
	reverse( str.begin(), str.end() );
	n = str.length();
	memset( s, 0, sizeof( s ) );
	for( int i = 0; i < n; i++ ) s[i] = str[i] - '0';
	ans = 0;
	for( int i = 0; i < n; i++ ) {
		if ( s[i] ) {
			int en = i;
			for( int j = i; j < n && s[j]; j++ ) en = j;
			ans++;
			for( int j = i; j <= en; j++ ) s[j] = 0;
			if ( en > i ) 
				s[en + 1] = 1;
		} 
	}
	if ( s[n] ) ans++;
	cout << ans << endl;
  return 0;
}

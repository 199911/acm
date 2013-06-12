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

int n, m, k, l;
int A[N], B[N], S[N], cnt[N];

int main() {
	cin >> n >> m >> k;
	REP( i, n ) cin >> A[i];
	REP( i, m ) cin >> B[i];
	l = 0;
	REP( i, n ) S[l++] = A[i];
	REP( i, m ) S[l++] = B[i];
	sort( S, S + l );
	l = unique( S, S + l ) - S;
	REP( i, n ) A[i] = lower_bound( S, S + l, A[i] ) - S;
	REP( i, m ) B[i] = lower_bound( S, S + l, B[i] ) - S;
	CLR( cnt, 0 );
	REP( i, n ) cnt[A[i]]++;
	REP( i, m ) cnt[B[i]]--;

	if ( n > m ) {
		printf( "YES\n" );
	} else {
		int x = 0;
		REP( i, l ) {
			if ( cnt[i] > 0 ) {
				if ( x < 0 ) x = 0;
			}
			x += cnt[i];
		}

		if ( x > 0 ) printf( "YES\n" );
		else printf( "NO\n" );
	}

  return 0;
}

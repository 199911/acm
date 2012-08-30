#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

char nm[111] = "23456789TJQKA";
char st[111] = "SDHC";

int hash( char card[2] ) {
	int a = 0, b = 0;
	for( a = 0; a < 13; a++ ) if ( card[0] == nm[a] ) break;
	for( b = 0; b < 4; b++ ) if ( card[1] == st[b] ) break;
	return 13 * b + a;
}

int dk[111], n;
bool dp[54][54][54][54];

#define COMP(a, b) ((a)/13==(b)/13||(a)%13==(b)%13)

int main() {
	scanf( "%d", &n );
	REP(i, n) {
		char in[111];
		scanf( "%s", in );
		dk[i] = hash(in);
	}

	if( n >= 3 ) {
		memset(dp, 0, sizeof(dp));

		dp[n-1][dk[n-1]][dk[n-2]][dk[n-3]] = 1;

		for(int i = n - 1; i >= 3; i-- ) {
			REP(j, 52) REP(k, 52) REP(l, 52) {
				if ( dp[i][j][k][l] ) {
					if ( COMP(j,k)) dp[i-1][j][l][dk[i-3]] = 1; 
					if ( COMP(j, dk[i-3]) ) dp[i-1][k][l][j] = 1;
				}
			}
		}

		int ok = 0;
		REP(j, 54) REP(k, 52) REP(l, 52) {
			if( dp[2][j][k][l] ) {
				if ( COMP(j,k) && COMP(j,l) || COMP(k,l) && COMP(j,k) ) ok = 1;
			}
		}

		printf("%s\n", ok ? "YES" : "NO");
	
	} else {
		if ( n == 1 ) puts("YES");
		else printf( "%s\n", COMP(dk[0],dk[1])?"YES":"NO");
	}

	return 0;
}

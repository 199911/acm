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

#define MOD 1000002013LL
#define M 1111
#define PLL pair<LL, LL>

int T;
LL N, cnt[M], tot, a[M], b[M], p[M];
LL stop[2 * M];
int m, nst;

LL go( LL d ) {
	return ( 2 * N - d + 1 ) * d / 2 % MOD;
}

PLL find( int st ) {
	LL pop = cnt[st], ptr = st + 1, lft = cnt[st];
	while( ptr < nst ) {
		if ( pop + cnt[ptr] <= 0 ) break;
		pop += cnt[ptr];
		lft = min( lft, pop );
		ptr++;
	}
	return PLL( ptr, lft );
}

int main() {
	int cas = 1;
	scanf( "%d", &T );
	while( T-- ) {
		CLR( cnt, 0 );
		scanf( "%lld%d", &N, &m );
		tot = 0;
		nst = 0;
		REP( i, m ) {
			scanf( "%lld%lld%lld", &a[i], &b[i], &p[i] );
			a[i]--; b[i]--;
			tot += go( b[i] - a[i] ) * p[i] % MOD;
			tot %= MOD;
			stop[nst++] = a[i];
			stop[nst++] = b[i];
		}

		sort( stop, stop + nst );
		nst = unique( stop, stop + nst ) - stop;

		REP( i, m ) {
			a[i] = lower_bound( stop, stop + nst, a[i] ) - stop;
			b[i] = lower_bound( stop, stop + nst, b[i] ) - stop;
			cnt[a[i]] += p[i];
			cnt[b[i]] -= p[i];
		}
		
		LL ntot = 0;
		REP( st, nst ) {
			if ( cnt[st] <= 0 ) continue;
			while( cnt[st] > 0 ) {
				PLL ans = find( st );
				LL en = ans.first, pp = ans.second;
//				printf( "find %d -> %lld | %lld\n", st, ans.first, ans.second );
				cnt[st] -= pp;
				cnt[en] += pp;
				ntot += go( stop[en] - stop[st] ) * pp % MOD;
				ntot %= MOD;
			}
		}

		printf( "Case #%d: %lld\n", cas++, ( ( tot - ntot ) % MOD + MOD ) % MOD );
	}
  return 0;
}

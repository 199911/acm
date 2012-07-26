#include <cstdio>
#include <iostream>
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

#define LL long long

LL p[111], cur, n, x[44], cnt[11];

int find( long long a ) {
	for(int i = 4; i >= 0; i--) {
		if ( a >= x[i] ) return i;
	}
	return -1;
}

int main() {
	cin >> n;
	REP(i, n) cin >> p[i];
	REP(i, 5) cin >> x[i];
	memset(cnt, 0, sizeof(cnt));
	cur = 0;

	REP(i, n) {
		cur += p[i]; 
		int dd;
		while( (dd = find(cur)) != -1) {
			cnt[dd] += cur / x[dd];
			cur %= x[dd];
		}
	}

	REP(i, 5) {
		cout << cnt[i];
		if( i < 4 ) cout << " ";
		else cout << endl;
	}
	cout << cur << endl;
	return 0;
}

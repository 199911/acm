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

int main() {
	int n, m, a[11111], b[11111];
	cin >> n;
	REP( i, n ) cin >> a[i] ;
	cin >> m;
	REP( i, m ) cin >> b[i];

	int ma = -1, cnt = 0;
	REP( i, n ) REP ( j, m ) {
		if ( b[j] % a[i] == 0 ) {
			if ( b[j] / a[i] > ma ) {
				cnt = 1;
				ma = b[j] / a[i];
			} else if ( b[j] / a[i] == ma ) {
				cnt++;
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}

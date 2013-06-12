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

#define N 22

int A[N], B[N], X[N], n, T;
int used[N];

bool check() {
	int tb[N];
//	REP( i, n ) printf( "%d ", X[i] );
//	puts( "" );
	for( int i = n - 1; i >= 0; i-- ) {
		tb[i] = 1;
		for( int j = i + 1; j < n; j++ ) 
			if ( X[i] > X[j] ) tb[i] = max( tb[i], tb[j] + 1 );
	}
	REP( i, n ) {
		if ( tb[i] != B[i] ) return false;
	}
//	printf( "hahaha\n" );
	return true;
}

bool dfs( int idx ) {
	if ( idx == n ) { 
//		puts( "haha" );
		return check(); 
	}
	REP( i, n ) {
		if ( !used[i] ) {
			int mx = 1;
			REP( j, idx ) if ( X[j] < i ) mx = max( A[j] + 1, mx );
			if ( mx == A[idx] ) {
				used[i] = 1;
				X[idx] = i;
//				printf( "X[%d] <- %d\n", idx, i ); 
				if ( dfs( idx + 1 ) ) { 
					used[i] = 0;
					return true;
				}
				used[i] = 0;
			}
		}
	}
	return false;
}

int main() {
	scanf( "%d", &T );
	FOE( cas, 1, T ) {
		printf( "Case #%d:", cas );
		scanf( "%d", &n );
		REP( i, n ) scanf( "%d", &A[i] );
		REP( i, n ) scanf( "%d", &B[i] );
		dfs(0);
		REP( i, n ) printf( " %d", X[i] + 1 );
		puts( "" );
	}
  return 0;
}

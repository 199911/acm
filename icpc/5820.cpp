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

#define MOD 19997

int exp( int a, int b, int m ) {
	int ret = 1;
	while( b ) {
		if ( b & 1 ) ( ret *= a ) %= m;
		( a *= a ) %= m;
		b >>= 1;
	}
	return ret;
}

int inv( int a, int p ) {
	return exp( a, p - 2, p );
}

int rank( int A[1200][1200], int m, int n, int p ) {
	int rnk = 0;
	for( int i = 0, row = 0; i < n && row < m; i++ ) {
		if ( A[row][i] == 0 ) 
			for( int j = row + 1; j < m; j++ ) 
				if ( A[j][i] ) {
					for( int k = i; k < n; k++ ) { 
						swap( A[row][k], A[j][k] );
					}
					break;
				}
		if ( A[row][i] ) {
			rnk++;
			int iv = inv( A[row][i], p );
			for( int j = row + 1; j < m; j++ ) {
				int mul = iv * A[j][i] % p;
				for( int k = i; k < n; k++ ) {
					A[j][k] -= A[row][k] * mul % p;
					A[j][k] = ( ( A[j][k] % p ) + p ) % p;
				}
			}
			row++;
		}

	}
	return rnk;
}

int C[1200][1200];

int linear_matroid_intersect( int A[1200][1200], int B[1200][1200], int m, int n, int r ) {
	int rnd[1200];
	int ans = -1;

	if ( m > n ) {
		swap( A, B );
		swap( m, n );
	}
	srand( time( NULL ) );
	for( int i = 0; i < r; i++ ) rnd[i] = rand() % MOD;
	for( int i = 0; i < m; i++ ) {
		for( int j = 0; j < n; j++ ) {
			C[i][j] = 0;
			for( int k = 0; k < r; k++ ) 
				( C[i][j] += A[i][k] * rnd[k] % MOD * B[j][k] % MOD ) %= MOD;
		}
	}
	return rank( C, m, n, MOD );
}

int R, r, m, n, k, a[333], b[333], c[333], d[333], srt[1222], mp[11111];
int A[1200][1200], B[1200][1200];

int main() {
	while( scanf( "%d", &R ), R ) {
		k = 0;
		for( int i = 0; i < R; i++ ) {
			scanf( "%d%d%d%d", a + i, b + i, c + i, d + i );
			srt[k++] = a[i];
			srt[k++] = b[i];
			srt[k++] = c[i];
			srt[k++] = d[i];
		}
		sort( srt, srt + k );
		k = unique( srt, srt + k ) - srt;
		for( int i = 0; i < k; i++ ) mp[srt[i]] = i;
		m = R;
		n = k;
		r = 2 * R;

		for( int i = 0; i < m; i++ ) for( int j = 0; j < r; j++ ) A[i][j] = 0;
		for( int i = 0; i < n; i++ ) for( int j = 0; j < r; j++ ) B[i][j] = 0;

		for( int i = 0; i < R; i++ ) {
			A[i][i * 2] = 1;
			A[i][i * 2 + 1] = 1;
			B[mp[a[i]]][i * 2] = 1;
			B[mp[b[i]]][i * 2] = MOD - 1;
			B[mp[c[i]]][i * 2 + 1] = 1;
			B[mp[d[i]]][i * 2 + 1] = MOD - 1;
		}

		printf( "%d\n", linear_matroid_intersect( A, B, m, n, r ) * 2 );
	}
	return 0;
}

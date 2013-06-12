#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int gr[111][111], n, m, tc, mr[111], mc[111];

int main() {
	scanf( "%d", &tc );
	for( int cas = 1; cas <= tc; cas++ ) {
		scanf( "%d%d", &m, &n );
		for( int i = 0; i < m; i++ ) 
			for( int j = 0; j < n; j++ ) 
				scanf( "%d", &gr[i][j] );
		for( int i = 0; i < m; i++ ) mr[i] = -1;
		for( int i = 0; i < n; i++ ) mc[i] = -1;

		for( int i = 0; i < m; i++ ) 
			for( int j = 0; j < n; j++ ) {
				mr[i] = max( mr[i], gr[i][j] );
				mc[j] = max( mc[j], gr[i][j] );
			}

		int ok = 1;
		for( int i = 0; i < m; i++ ) 
			for( int j = 0; j < n; j++ ) 
				if ( gr[i][j] != min( mr[i], mc[j] ) ) ok = 0;

		printf( "Case #%d: %s\n", cas, ok ? "YES" : "NO" );
	}

}

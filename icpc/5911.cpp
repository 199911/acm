#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

void print( int k, int w ){
	for( int i = w - 1; i >= 0; i-- ) {
		printf( "%d", k & (1 << i) ? 1 : 0 );
	}
	puts( "" );
}

int main() {
	int m, n, k, N = 0;
	while( scanf( "%d", &m ) != EOF ) {
		for( n = 0; ( 1 << n ) < m; n++ );
		k = ( 1 << n ) - m;
		int u = 1 << n - 1;
		for( int i = 0; i < u; i++ ) {
			if ( i < k ) print( i, n - 1 );
			else {
				print( i << 1, n  );
				print( ( i << 1 ) + 1, n );
			}
		}
	}
	return 0;
}

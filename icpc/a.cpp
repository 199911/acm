#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MOD 1000000007

int f[111111], T, n, k;

int main() {
	scanf( "%d", &T );
	while( T-- ) {
		scanf( "%d%d", &n, &k );
		if ( n < k ) k = n - 1;
		for( int i = 0; i < k + 2; i++ ) f[i] = i + 1;
		for( int i = k + 2; i <= n; i++ ) 
			f[i] = (f[i - 1] + f[i - k - 1] ) % MOD;
		printf( "%d\n", (f[n] + MOD - 1 ) % MOD );

	}
	return 0;
}

#include <cstdio>
#include <cstring>

bool it[1<<25];
int mp[2222];
int n, p;

int main() {
	scanf( "%d%d", &n, &p );
	int mx = 1, cur = 0, x, hs = 0;
	for( int i = 0; i < n; i++ ) mx *= p;
	getchar();

	memset( it, 0, sizeof( it ) );
	memset( mp, -1, sizeof( mp ) );
	int sz = 0;

	while( ( x = getchar() ) != '\n' ) {
		if ( mp[x] == -1 ) {
			mp[x] = sz++;
		}
		x = mp[x];
		hs *= p;
		hs += x;
		hs %= mx;
		if ( ++cur >= n ) it[hs] = 1;
	}

	int ans = 0;
	for( int i = 0; i < mx; i++ ) ans += it[i]; 

	printf( "%d\n", ans ) ;

	return 0;
}

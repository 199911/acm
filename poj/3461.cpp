#include <cstdio>
#include <cstring>

#define N 1000055

char s[N], t[N];
int f[N], n, m;

int solve() {
	scanf( "%s%s", s, t );
	n = strlen( s );
	m = strlen( t );
	memset( f, 0, sizeof( f ) );

	for( int i = 1, p = 0; i < n; i++ ) {
		while ( p && s[i] != s[p] ) p = f[p - 1];
		if ( s[i] == s[p] ) p++;
		f[i] = p;
	}

	int cnt = 0;
	for( int i = 0, p = 0; i < m; i++ ) {
		while ( p && t[i] != s[p] ) p = f[p - 1];
		if ( t[i] == s[p] ) p++;
		if ( p == n ) {
			cnt++;
		}
	}

	printf( "%d\n", cnt );

	return 0;
}

int main() {
	int T;
	scanf( "%d", &T );
	while( T-- ) solve();
	return 0;
}

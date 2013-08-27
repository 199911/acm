#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 2000000

int d[N], nt[N], to[N], hd[N], en, n, m;
int ce[N], cc, co[N];

void init() {
	memset( hd, -1, sizeof( hd ) );
	memset( d, 0, sizeof( d ) );
	en = 0;
}

void add( int a, int b ) {
	to[en] = b; nt[en] = hd[a]; hd[a] = en++;
	to[en] = a; nt[en] = hd[b]; hd[b] = en++;
	d[a]++; d[b]++;
}

int vis[N];

int dfs( int a ) {
	vis[a] = 1;
	co[cc] += d[a] % 2;
	for( int e = hd[a]; e != -1; e = nt[e] ) { 
		ce[cc]++;
		if ( !vis[to[e]] ) {
			dfs( to[e] );
		}
	}
	return co[cc];
}

int main() {
	scanf( "%d%d", &n, &m );
	init();
	for( int i = 0; i < m; i++ ) {
		int a, b;
		scanf( "%d%d", &a, &b );
		a--; b--;
		add( a, b );
	}
	int tot = 0, tot0 = 0;
	cc = 0;
	memset( vis, 0, sizeof( vis ) );
	memset( co, 0, sizeof( co ) );
	memset( ce, 0, sizeof( ce ) );
	for( int i = 0; i < n; i++ ) {
		if ( vis[i] == 0 ) {
			dfs( i );
			if ( !cc || ce[cc] ) cc++;
		}
	}
	if ( cc == 0 ) {
		puts( "0" );
	} else if ( cc == 1 ) {
		printf( "%d\n", co[0] / 2 );
	} else {
		int tot = 0;
		for( int i = 0; i < cc; i++ ) {
			if ( i == 0 ) {
				tot += co[i];
				if ( ce[0] < en && co[0] <= 1 ) tot += 2;
			} else {
				tot += co[i];
				if ( co[i] <= 1 ) tot += 2;
			}
		}
		if ( en ) printf( "%d\n", tot / 2 );
		else puts( "0" );
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 111111

int pl[N], ip[N], bit[N], pn, n;

int main() {
	for( int i = 0; i < N; i++ ) ip[i] = 1;
	pn = 0;
	for( int i = 2; i < N; i++ ) 
		if ( ip[i] ) {
			pl[pn++] = i;
			for( int j = i + i; j < N; j +=i ) ip[j] = 0;
		}

	while( scanf( "%d", &n ) != EOF ) {
		for( int i = 0; i < N; i++ ) bit[i] = 1;

		int bg = 0, en = 0;
		for( int i = 0; i < pn; i++ ) 
			if( pl[i] <= n ) en = i;

		int ans = 0;
		while( bg <= en ) {
			if ( pl[bg] * pl[en] <= n ) {
				bg++; en--;
			} else {
				en--;
			}
			ans++;
		}
		printf( "%d\n", ans );
	}

	return 0;
}

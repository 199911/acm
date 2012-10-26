#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int A[111111], n, srt[111111];
	scanf( "%d", &n );
	for( int i = 0; i < n; i++ ) {
		scanf( "%d", &A[i]);
		srt[i] = A[i];
	}

	sort( srt, srt + n );

	int cnt = 0;
	for( int i = 0; i < n; i++ ) {
		if ( srt[i] != A[i] ) cnt++;
	}
	if ( cnt <= 2 ) puts( "YES" );
	else puts( "NO" );
	return 0;
}

#include <cstdio>
#include <cstring>
using namespace std;

char g[11][11];
int tc;

int main() {
	scanf( "%d", &tc );
	for( int cas = 1; cas <= tc; cas++ ) {
		for( int i = 0; i < 4; i++ ) scanf( "%s", g[i] );
		int st = -1, cnt[111];

		for( int i = 0; i < 4; i++ ) {
			memset( cnt, 0, sizeof( cnt ) );
			for( int j = 0; j < 4; j++ ) 
				cnt[g[i][j]]++;
			if ( cnt['X'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 1;
			if ( cnt['O'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 2;
			if ( cnt['.'] > 0 && st == -1 ) st = 0; 
		}
		for( int i = 0; i < 4; i++ ) {
			memset( cnt, 0, sizeof( cnt ) );
			for( int j = 0; j < 4; j++ ) 
				cnt[g[j][i]]++;
			if ( cnt['X'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 1;
			if ( cnt['O'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 2;
			if ( cnt['.'] > 0 && st == -1 ) st = 0; 
		}

		memset( cnt, 0, sizeof( cnt ) );
		for( int j = 0; j < 4; j++ ) 
			cnt[g[j][j]]++;
		if ( cnt['X'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 1;
		if ( cnt['O'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 2;
		if ( cnt['.'] > 0 && st == -1 )  st = 0; 

		memset( cnt, 0, sizeof( cnt ) );
		for( int j = 0; j < 4; j++ ) 
			cnt[g[j][3 - j]]++;
		if ( cnt['X'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 1;
		if ( cnt['O'] + cnt['T'] == 4 && cnt['T'] <= 1 ) st = 2;
		if ( cnt['.'] > 0 && st == -1 ) st = 0; 

		printf( "Case #%d: ", cas );
		if ( st == -1 ) printf( "Draw\n" );
		else if ( st == 0 ) printf( "Game has not completed\n" );
		else if ( st == 1 ) printf( "X won\n" );
		else printf( "O won\n" );
	}
	return 0;
}

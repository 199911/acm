#include <cstdio>
#include <cstring>

int h, w, dx[5] = {0, 1, 0, -1}, dy[5] = {1, 0, -1, 0};
char gr[22][22];

void go( int i, int j ) {
  gr[i][j] = 'x';
  for( int d = 0; d < 4; d++ ) {
    int ti = i + dx[d], tj = j + dy[d];
    if ( ti < 0 || ti == h || tj < 0 || tj == w ) continue;
    if ( gr[ti][tj] == '.' ) go( ti, tj );
  }
}

int main() {
  while( scanf( "%d%d", &w, &h ), w || h ) {
    for( int i = 0; i < h; i++ )  scanf( "%s", gr[i] );
    for( int i = 0; i < h; i++ ) 
      for( int j = 0; j < w; j++ ) 
        if ( gr[i][j] == '@' ) 
          go( i, j );
    int ans = 0;
    for( int i = 0; i < h; i++ )
      for( int j = 0; j < w; j++ ) 
        if ( gr[i][j] == 'x' ) 
          ans++;
    printf( "%d\n", ans );
  }
  return 0;
}

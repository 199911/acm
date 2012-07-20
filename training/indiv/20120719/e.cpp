#include <cstdio>
#include <cstring>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);i++) 
#define REP(i,n) FOR(i,0,n)

int k, p, cat[1111][22], mtc[1111][22], my[1111];
int nk[22], np[1111], cp[22], ok, uk[22], vis[22];

int path(int x) {
  vis[x] = 1;
  for(int y = 0; y < p; y++) {
    if ( cat[y][x] && my[y] != x && ( my[y] == -1 || !vis[my[y]] && path(my[y])) ) {
//      printf("map %d %d\n", x, y);
      my[y] = x;
      return 1;
    }
  }
  return 0;
}

int main() {
  while ( scanf( "%d%d", &k, &p ), k || p) {
    for(int i = 0; i < k; i++ ) scanf( "%d", &nk[i] );
    memset(cat, 0, sizeof(cat));

    for(int i = 0; i < p; i++ ) {
      scanf( "%d", &cp[i] );
      for(int j = 0; j < cp[i]; j++) {
        int x;
        scanf( "%d", &x );
        x--;
        cat[i][x] = 1;
      }
    }

    ok = 1;
    memset(my, -1, sizeof(my));
    for(int i = 0; i < k; i++) {
      uk[i] = nk[i];
      while( memset(vis, 0, sizeof(vis)), uk[i] && path(i) ) {
        uk[i]--;
      }
      if ( uk[i] ) ok = 0;
    }

    printf("%d\n", ok);
    if ( ok ) {
      for( int i = 0; i < k; i++) {
        for( int j = 0; j < p; j++ ) {
          if( my[j] == i ) {
            printf("%d%s", j + 1, --nk[i]? " " : "\n");
          }
        }
      }
    }
  }
  return 0;
}

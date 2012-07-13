#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 222

int adj[N][N], na, nb;
int ma[N], mb[N], va[N], vb[N];

int path( int x ) {
  va[x] = 1;
  for ( int  y = 0; y < nb; y++ ) {
    if( adj[x][y] && !vb[y] ) {
      vb[y] = 1;
      if ( mb[y] == -1 || path( mb[y] ) ) {
        mb[y] = x;
        ma[x] = y;
        return 1;
      }
    }
  }
  return 0;
}

int mat() {
  int cnt = 0;
  for(int i = 0; i < na; i++) {
    memset(va, 0, sizeof(va));
    memset(vb, 0, sizeof(vb));
    cnt += path(i);
  }
  return cnt;
}

int main() {
  while( scanf( "%d%d", &na, &nb) != EOF ) {
    memset(adj, 0, sizeof(adj));
    memset(ma, -1, sizeof(ma));
    memset(mb, -1, sizeof(mb));
    for(int i = 0; i < na; i++) {
      int k;
      scanf( "%d", &k );
      for(int j = 0; j < k; j++) {
        int x;
        scanf("%d", &x);
        x--;
        adj[i][x] = 1;
      }
    }
    printf( "%d\n", mat() );
  }

  return 0;
}

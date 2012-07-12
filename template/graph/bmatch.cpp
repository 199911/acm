#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

#define N 222

int adj[N][N], na, nb, m;

int ma[N], mb[N], va[N], vb[N];

void init() {
  memset(adj, 0, sizeof(adj));
  m = na = nb = 0;
  memset(ma, -1, sizeof(ma));
  memset(mb, -1, sizeof(mb));
}

int path(int x) {
  va[x] = 1;
  for(int y = 0; y < nb; y++) {
    if( adj[x][y] && !vb[y] ) {
      vb[y] = 1;
      if( mb[y] == -1 || path(mb[y]) ) {
        ma[x] = y; mb[y] = x; 
        return 1;
      }
    }
  }
  return 0;
}

int bmatch() {
  int cnt = 0;
  REP(x, na) {
    memset(va, 0, sizeof(va));
    memset(vb, 0, sizeof(vb));
    cnt += path(x);
  }
  return cnt;
}

int main() {
  init();
  scanf( "%d%d%d", &na, &nb, &m );
  REP(i, m) {
    int a, b;
    scanf( "%d%d", &a, &b);
    adj[a][b] = 1;
  }

  int cnt = bmatch();
  printf("%d\n", cnt);
  REP(x, na) {
    if( ma[x] != -1 ) printf("%d->%d\n", x, ma[x]);
  }

  return 0;
}

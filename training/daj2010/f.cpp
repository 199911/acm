#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

#define N 5001
#define M 25000003

struct E {
  int u, v, w;
  E() {}
  E(int u, int v, int w): u(u), v(v), w(w) {}
  bool operator<( const E &e ) const {
    return w > e.w;
  }
} edge[M];


int pp[N], n, m, T, size[N];
set<int> chg;

void make_set() {
  REP( i, n ) { 
    pp[i] = i;
    size[i] = 1;
  }
}

int find( int x ) {
  return x == pp[x] ? ( x ) : ( pp[x] = find(pp[x]));
}

void join( int x, int y ) {
  if ( find( x ) != find(y) ) {
    size[find(y)] += size[find(x)];
    chg.erase( find(x) );
    chg.insert( find(y) );
    pp[find(x)] = find(y);
  }
}

int main() {
  scanf( "%d", &T );
  while( T-- ) {
    scanf( "%d%d", &n, &m );
    REP( i, m ) {
      int u, v, w;
      scanf( "%d%d%d", &u, &v, &w );
      edge[i] = E( u - 1, v - 1, w );
    }
    make_set();

    int ans = 0;
    sort( edge, edge + m );
    for( int i = 0, j = 0; i < m; i = j) {
      chg.clear();
      while( j < m && edge[j].w == edge[i].w ) {
        join( edge[j].u, edge[j].v );
        j++;
      }
      for( set<int>::iterator it = chg.begin(); it != chg.end(); it++ ) {
        ans += size[*it];
      }
    }

    printf( "%d\n", ans );

  }
  return 0;
}

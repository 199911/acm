#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 11111

int hd[N], nt[N], to[N], fr[N], en, n;

void init() {
  memset( hd, -1, sizeof( hd ) );
  en = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; hd[a] = en++;
  to[en] = a; nt[en] = hd[b]; hd[b] = en++;
}

int dist[N], pr[N];

void dfs( int x ) {
  for( int e = hd[x]; e != -1; e = nt[e] ) 
    if ( dist[to[e]] == -1 ) {
      dist[to[e]] = dist[x] + 1;
      pr[to[e]] = x;
      dfs( to[e] );
    }
}

int main() {
  while( scanf( "%d", &n ), n ) {
    init();
    for( int i = 0; i < n - 1; i++ ) {
      int a, b;
      scanf( "%d%d", &a, &b );
      a--; b--;
      add( a, b );
    }
    int q;
    scanf( "%d", &q );
    while ( q-- ) {
    int a, b;
    scanf( "%d%d", &a, &b );
    a--; b--;
    memset( dist, -1, sizeof( dist ) );
    memset( pr, -1, sizeof( pr ) );
    dist[a] = 0;
    dfs( a );
    if ( dist[b] & 1 ) {
      int st = dist[b] / 2;
      int x = b, y;
      for( int i = 0; i < st; i++ ) 
        x = pr[x];
      y = pr[x];
      if ( x > y ) swap( x, y );
      printf( "The fleas jump forever between %d and %d.\n", x + 1, y + 1 );
    } else {
      int st = dist[b] / 2;
      int x = b;
      for( int i = 0; i < st; i++ ) x = pr[x];
      printf( "The fleas meet at %d.\n", x + 1 );
    }
    }
  }
  return 0;
}

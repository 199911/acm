#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

#define N 111
#define M 11111

int hd[N], nt[M], to[M], indeg[N], en, n, m;

void init() {
  memset( hd, -1, sizeof(hd) );
  en = 0;
}

void add( int a, int b ) {
  to[en] = b; nt[en] = hd[a]; hd[a] = en++;
}

int doit( char str[] ) {
  int q[N], qh, qt, lf = n, ptr = 0, ret = 0;
  qh = 0; qt = 0;
  memset( indeg, 0, sizeof( indeg ) );
  for( int i = 0; i < en; i++ ) indeg[to[i]]++;
  for( int i = 0; i < n; i++ ) if ( indeg[i] == 0 ) q[qt++] = i;
  while( qt != qh ) {
    if ( qt > qh + 1 ) ret = 1;
    int w = q[qh++];
    lf--;
    for( int e = hd[w]; e != -1; e = nt[e] ) 
      if( --indeg[to[e]] == 0 ) 
        q[qt++] = to[e];
    str[ptr++] = 'A' + w;
  }
  if ( lf ) return 2; 
  if ( ret ) return 0;
  str[ptr] = 0;
  return 1;
}

int main() {
  while( scanf( "%d%d", &n, &m ), n || m ) {
    init();
    int jmp = 0;
    for( int i = 0; i < m; i++ ) {
      char t[11], ans[33] = "";
      scanf( "%s", t );
      if( jmp ) continue;
      add( t[0] - 'A', t[2] - 'A' );
      int f = doit( ans );
      if ( f == 1 ) {
        printf( "Sorted sequence determined after %d relations: %s.\n", i + 1, ans );
        jmp = 1;
      } else if ( f == 2 ) {
        printf( "Inconsistency found after %d relations.\n", i + 1 );
        jmp = 1;
      }
    }
    if ( !jmp ) printf( "Sorted sequence cannot be determined.\n" );
  }
  return 0;
}

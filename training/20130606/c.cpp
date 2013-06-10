#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 111

int a, b, c, pr[N*N], q[N * N], qt, qh, tp[N * N], tg[N * N], dist[N];

int bfs( int s ) {
  memset( pr, -1, sizeof( pr ) );
  qt = qh = 0;
  q[qt++] = s;
  pr[s] = 0;
  dist[s] = 0;
  int ans = -1;
  while( qt > qh ) {
    int st = q[qh++];
    int aa = st / ( b + 1 ), bb = st % ( b + 1 );
    int ns;

    if ( aa == c || bb == c ) return st;

    ns = a * ( b + 1 ) + bb;
    if ( pr[ns] == -1 ) {
      dist[ns] = dist[st] + 1;
      tg[ns] = 1;
      tp[ns] = 0;
      pr[ns] = st;
      q[qt++] = ns;
    }

    ns = bb;
    if ( pr[ns] == -1 ) {
      dist[ns] = dist[st] + 1;
      tp[ns] = 1;
      tg[ns] = 1;
      pr[ns] = st;
      q[qt++] = ns;
    }

    int tmp = min( aa, b - bb ), naa = aa - tmp, nbb = bb + tmp;
    ns = naa * ( b + 1 ) + nbb;
    if ( pr[ns] == -1 ) {
      dist[ns] = dist[st] + 1;
      tg[ns] = 1;
      tp[ns] = 2;
      pr[ns] = st;
      q[qt++] = ns;
    }

    ns = aa * ( b + 1 ) + b; 
    if ( pr[ns] == -1 ) {
      dist[ns] = dist[st] + 1;
      tg[ns] = 2;
      tp[ns] = 0;
      pr[ns] = st;
      q[qt++] = ns;
    }

    ns = aa * ( b + 1 );
    if ( pr[ns] == -1 ) {
      dist[ns] = dist[st] + 1;
      tg[ns] = 2;
      tp[ns] = 1;
      pr[ns] = st;
      q[qt++] = ns;
    }

    tmp = min( bb, a - aa );
    naa = aa + tmp;
    nbb = bb - tmp;
    ns = naa * ( b + 1 ) + nbb;
    if ( pr[ns] == -1 ) {
      dist[ns] = dist[st] + 1;
      tg[ns] = 2;
      tp[ns] = 2;
      pr[ns] = st;
      q[qt++] = ns;
    }
  }

  return -1;
}

void trace( int st ) {
  if( st <= 0 ) return;
  trace( pr[st] );

  if ( tp[st] == 0 ) {
    printf( "FILL(%d)\n", tg[st] );
  } else if ( tp[st] == 1 ) {
    printf( "DROP(%d)\n", tg[st] );
  } else {
    printf( "POUR(%d,%d)\n", tg[st], 3 - tg[st] );
  }
}

int main() {
  scanf( "%d%d%d", &a, &b, &c );
  int ans = bfs( 0 );
  if( ans == -1 ) printf( "impossible\n" ); 
  else {
    printf( "%d\n", dist[ans] );
    trace( ans );
  }
  return 0;
}

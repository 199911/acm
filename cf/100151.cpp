#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 222222
#define INF 111111111

int hd[N], nt[N], to[N], we[N], pr[N], pi[N], vld[N], rem[N], rem1[N], rem2[N], rem3[N], en, n;

void init() {
  en = 0;
  memset( hd, -1, sizeof( hd ) );
}

void add( int u, int v, int w, int p ) {
  to[en] = v; pr[en] = p; we[en] = w; nt[en] = hd[u]; hd[u] = en++;
  to[en] = u; pr[en] = p; we[en] = w; nt[en] = hd[v]; hd[v] = en++;
}

int vis[N], dist[N];

void dfs_dist_re( int x ) {
  vis[x] = 1;
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    int y = to[e];
    if ( vis[y] ) continue;
    pi[y] = x;
    dist[y] = dist[x] + we[e];
    dfs_dist_re( y );
  }
}

// return a furthest point
int dfs_dist( int s ) {
  memset( vis, 0, sizeof( vis ) );
  memset( pi, -1, sizeof( pi ) );
  memset( dist, 0, sizeof( dist ) );
  dist[s] = 0;
  dfs_dist_re( s );
  int ret = 0;
  for( int i = 0; i < n; i++ ) 
    if ( dist[i] > dist[ret] ) ret = i;
  return ret;
}

int diameter( int &s, int &t, int &m1, int &m2) {
  s = dfs_dist( 0 );
  t = dfs_dist( s );
  m1 = t; m2 = t;
  while( dist[m1] * 2 > dist[t]  ) {
    m1 = pi[m1]; 
  }
  while( dist[pi[m2]] * 2 >= dist[t] ) {
    m2 = pi[m2];
  }

  return dist[t];
}


int dfs_label_re( int x, int A[] ) {
  int flg = A[x];
  vis[x] = 1;
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    int y = to[e];
    if ( vis[y] ) continue;
    if ( dfs_label_re( y, A ) ) {
      flg = 1;
      vld[e] = 1; 
    } 
  }
  return flg;
}

void dfs_label( int s, int A[] ) {
  memset( vis, 0, sizeof( vis ) );
  memset( vld, 0, sizeof( vld ) );
  memset( pi, -1, sizeof( pi ) );
  dfs_label_re( s, A );
}

int dp[N];
int disconnect( int root, int lf[] ) {
  dp[root] = 0;
  for( int e = hd[root]; e != -1; e = nt[e] ) {
    if ( !vld[e] ) continue;
    disconnect( to[e], lf );
    if ( pr[e] < dp[to[e]] ) { 
      rem[e] = 1;
      dp[root] += pr[e];
    } else {
      rem[e] = 0;
      dp[root] += dp[to[e]];
    }
  }

  if ( lf[root] ) dp[root] = INF;
  return dp[root];
}


void dfs_remove_re( int x ) {
  vis[x] = 1;
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    if ( !vld[e] || vis[to[e]] ) continue;
    if ( dp[to[e]] > pr[e] ) rem[e] = 1;
    else dfs_remove_re(to[e]);
  }
}

void dfs_remove( int s ) {
  memset( rem, 0, sizeof( rem ) );
  memset( vis, 0, sizeof( vis ) );
  dfs_remove_re( s );
}

void dfs_unremove( int x, int pv ) {
  for( int e = hd[x]; e != -1; e = nt[e] ) {
    if ( to[e] == pv ) continue;
    if ( vld[e] ) {
      rem[e] = 0;
      dfs_unremove( to[e], x );
    }
  }
}

int lf[N], rc[N];
int find_leaves( int s, int t, int m ) {
  dfs_dist( m );
  int md = 0;
  for( int i = 0; i < n; i++ ) 
    if ( dist[i] > md ) 
      md = dist[i];
  
  for( int i = 0; i < n; i++ ) 
    lf[i] = dist[i] == md;

  dfs_label( m, lf );
  memset( rem, 0, sizeof( rem ) );
  memset( dp, 0, sizeof( dp ) );
  disconnect( m, lf );
  dfs_remove( m );
  int mb = 0, b = -1, me = -1;
  for( int e = hd[m]; e != -1; e = nt[e] ) {
    if ( vld[e] == 0 ) continue;
    int tmp = min( dp[to[e]], pr[e] );
    if ( tmp > mb ) {
      mb = tmp;
      me = e;
      b = to[e];
    }
  }

  if ( rem[me] ) rem[me] = 0;
  else {
    dfs_unremove( m, b );
  }
  return dp[m] - mb;
}

int find_leaves_2( int s, int t, int m1, int m2 ) {
  int md = 0, ans = 1<<30, am1, am2, am3;
  dfs_dist( s );
  memset( lf, 0, sizeof( lf ) );
  for( int i = 0; i < n; i++ ) 
    if ( md < dist[i] ) 
      md = dist[i];
  for( int i = 0; i < n; i++ ) 
    lf[i] = dist[i] == md;
  dfs_label( m2, lf );
  // disconnect m2 from lf

  am2 = disconnect( m2, lf );
  dfs_remove( m2 );
  copy( rem, rem + N, rem2 );

  dfs_dist( t );
  memset( lf, 0, sizeof( lf ) );
  for( int i = 0; i < n; i++ ) 
    if ( md < dist[i] )
      md = dist[i];

  for( int i =0; i < n; i++ )
    lf[i] = dist[i] == md;

  dfs_label( m1, lf );
  // disconnect m1 from label
  am1 = disconnect( m1, lf ); 
  dfs_remove( m1 );
  copy( rem, rem + N, rem1 );

  am3 = 1<<30;
  memset( rem3, 0, sizeof( rem3 ) );
  for( int e = hd[m1]; e != -1; e = nt[e] ) 
    if( to[e] == m2 ) {
      am3 = pr[e];
      rem3[e] = 1;
    }

  ans = min( am1, min( am2, am3 ) );

  if ( ans == am1 ) copy( rem1, rem1 + N, rem );
  else if( ans == am2 ) copy( rem2, rem2 + N, rem );
  else copy( rem3, rem3 + N, rem );

  return ans;
}



int main() {
//  freopen( "input.txt", "r", stdin );
//  freopen( "output.txt", "w", stdout );
  scanf( "%d", &n );
  init();
  for( int i = 0; i < n - 1; i++ ) {
    int u, v, w, p;
    scanf( "%d%d%d%d", &u, &v, &w, &p );
    u--; v--;
    add( u, v, w, p );
  }
  int s, t, m1, m2, ans;
  diameter( s, t, m1, m2 );

  //printf( "%d -> %d : [%d, %d]\n", s + 1, t + 1, m1 + 1, m2 + 1 );

  if ( m1 == m2 ) {
    ans = find_leaves( s, t, m1 );
  } else {
    ans = find_leaves_2( s, t, m1, m2 );
  }

  printf( "%d\n", ans );

  int cnt = 0;
  for( int i = 0; i < en; i++ ) if ( rem[i] ) cnt++;
  printf( "%d\n", cnt );
  for( int i = 0; i < en; i++ ) {
    if ( rem[i] ) {
      printf( "%d%s", i / 2 + 1, --cnt ? " " : "\n" );
    }
  }

  return 0;
}

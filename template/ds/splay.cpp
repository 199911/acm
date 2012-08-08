#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

#define N 111111

// pointer allocation
int nt[N], hd;

void init() {
  hd = 0;
  REP( i, N - 1 ) nt[i] = i + 1;
  nt[N - 1] = -1;
}

int new_node() {
  int ret = hd;
  hd = nt[hd];
  return ret;
}

void free_node( int idx ) {
  nt[idx] = hd;
  hd = idx;
}

int p[N], l[N], r[N], key[N], root, sz;

void init_tree() {
  memset( p, -1, sizeof(p) );
  memset( l, -1, sizeof(l) );
  memset( r, -1, sizeof(r) );
  root = -1;
  sz = 0;
}

void lrot( int x ) {
  int y = r[x];

  r[x] = l[y];
  if ( l[y] != -1 ) 
    p[l[y]] = x;

  p[y] = p[x];
  if ( p[x] == -1 ) 
    root = y;
  else if ( x == l[p[x]] ) 
    l[p[x]] = y;
  else 
    r[p[x]] = y;

  l[y] = x;
  p[x] = y;
}

void rrot( int y ) {
  int x = l[y];

  l[y] = r[x];
  if ( r[x] != -1 ) 
    p[r[x]] = y;

  p[x] = p[y];

  if ( p[y] == -1 ) 
    root = x;
  else if ( y == l[p[y]] ) 
    l[p[y]] = x;
  else 
    r[p[y]] = x;

  r[x] = y;
  p[y] = x;
}

bool splay_step( int x, int tg ) {
  if ( x == tg ) return true;
  if ( p[x] == tg ) {
    if ( x == l[p[x]] ) rrot( p[x] );
    else lrot( p[x] );
    return true;
  } else {
    int y = p[x], z = p[p[x]];
    if ( y == l[z] && x == l[y] ) {
      rrot( z );
      rrot( y );
    } else if ( y == r[z] && x == r[y] ) {
      lrot( z );
      lrot( y );
    } else if ( y == l[z] && x == r[y] ) {
      lrot( y );
      rrot( z );
    } else {
      rrot( y );
      lrot( z ); 
    }
    return z == tg;
  }
}

void splay( int x, int tg ) {
  while ( !splay_step( x, tg ) );
}

int find( int k ) {
  int p = root, y = -1;

  while ( p != -1 && k != key[p] ) {
    y = p;
    p = k < key[p] ? l[p] : r[p];
  }

  if ( p != -1 ) splay( p, root );

  return p;
}

int find_min() {
  if ( sz == 0 ) return INF; 
  int x = root;

  while ( l[x] != -1 ) x = l[x];

  splay( x, root );

  return key[x];
}

int find_max() {
  if ( sz == 0 ) return -INF;
  int x = root;

  while ( r[x] != -1 ) x = r[x];

  splay( x, root );

  return key[x];
}

int insert( int k ) {
  int nd = new_node();
  if ( nd == -1 ) return 0;
  key[nd] = k;

  int x = root, y = -1;

  while ( x != -1 && k != key[x] ) {
    y = x;
    x = k < key[x] ? l[x] : r[x]; 
  }

  if ( x != -1 ) return 0;
  
  if ( y == -1 ) root = nd;
  else if ( k < key[y] ) l[y] = nd;
  else r[y] = nd;

  p[nd] = y;
  l[nd] = r[nd] = -1;

  sz++;

  splay( nd, root );

  return 1;
}

int remove( int k ) {
  int nd = find( k );

  if ( nd == -1 ) return 0;

  int x = l[nd];

  if ( x == -1 ) {
    p[r[root]] = -1;
    root = r[nd];

    free_node( nd );
  } else {
    int y = r[nd];
    p[x] = -1;
    root = x;

    free_node( nd );

    find_max();

    p[y] = root;
    r[root] = y;
  }

  sz--;

  return 1;
}

void print( int nd ) {
  if ( nd == -1 ) return;
  printf( "%d(%d) [ ", key[nd], nd );
  print( l[nd] );
  printf( " : ");
  print( r[nd] );
  printf( " ]");
}

int main() {
  init(); init_tree();

  int k, c;
  while ( cin >> c >> k ) {
    if ( c == 1 ) insert( k );
    else remove( k );
    print( root );
    puts( "" );
  }
  return 0;
}

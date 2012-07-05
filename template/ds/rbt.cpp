// red black tree

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

#define N 10000


int mul[N], key[N], left[N], right[N], color[N], p[N], root, n;	// tree structure
int mhd, mnt[N];	// memonry

void init() {
	memset(left, -1, sizeof(left));
	memset(right, -1, sizeof(right));
	memset(p, -1, sizeof(right));
	memset(mul, 0, sizeof(mul));

	REP(i, N -1) mnt[i] = i + 1; 
	mnt[N - 1] = -1;
	mhd = 0;

	n = 0;
	root = -1;
}

int new_node() {
	int ret = mhd;
	mhd = mnt[mhd];
	return ret;
}

void free_node(int x) {
	mnt[x] = mhd;
	mhd = x;
}

// rotate x to the left of its right child
void lrot(int x) {
	int y = right[x];
	right[x] = left[y];
	if( left[y] != -1 ) p[left[y]] = x;
	p[y] = p[x];
	if( p[x] == -1 ) root = y;
	else if ( x == left[p[x]] ) left[p[x]] = y;
	else right[p[x]] = y;
	left[y] = x;
	p[x] = y;
}

// rotate x to the right of its left child
void rrot(int x) {
	int y = left[x];
	left[x] = right[y];
	if( right[y] != -1 ) p[right[y]] = x;
	p[y] = p[x];
	if( p[x] == -1 ) root = y;
	else if ( x == left[p[x]] ) left[p[x]] = y;
	else right[p[x]] = y;
	right[y] = x;
	p[x] = y;
}

int find_min(int x) {
  int y = p[x];
  while( x != -1 ) {
    y = x;
    x = left[x];
  }
  return y;
}

int successor(int x) {
  if( right[x] != -1 ) return find_min( right[x] );
  while ( p[x] != -1 && x == right[p[x]] ) {
    x = p[x];
  }
  return p[x];
}

void fix_insert(int x) {
	while( color[p[x]] == 1) {
		if( p[x] == left[p[p[x]]] ) {
			int y = right[p[p[x]]];
			if( color[y] == 1 ) {
				color[p[x]] = 0;
				color[y] = 0;
				color[p[p[x]]] = 1;
				x = p[p[x]];
			} else {
				if( x == right[p[x]] ) {
					// swing it to the left
					x = p[x];
					lrot(x);
				}
				color[p[x]] = 0;
				color[p[p[x]]] = 1;
				rrot( p[p[x]] );
			}
		} else {
			int y = left[p[p[x]]];
			if( color[y] == 1 ) {
				color[p[x]] = 0;
				color[y] = 0;
				color[p[p[x]]] = 1;
				x = p[p[x]];
			} else {
				if( x == left[p[x]] ) {
					x = p[x];
					rrot(x);
				}
				color[p[x]] = 0;
				color[p[p[x]]] = 1;
				lrot( p[p[x]] );
			}
		}
	}
	color[root] = 0;
}

int insert(int k) {
	// find the
	int x = root, y = -1;
	while ( x != -1 ) {
		y = x;
		if ( key[x] == k ) {
			mul[x]++;
			return mul[x];
		} else {
			x = key[x] < k ? right[x] : left[x];
		}
	}

	int z = new_node(); 
	key[z] = k;
	left[z] = right[z] = -1;
	p[z] = y;
  mul[z] = 1;
	if( y == -1 ) root = z;
	color[z] = 1; 
	if( k < key[y] ) left[y] = z;
	else right[y] = z;

	fix_insert(z);

	return 1;
}

void print(int x) {
  printf( " left " );
	if( left[x] != -1 ) print( left[x] );
  printf( " up ");
	printf("%d ", key[x] );
  printf( " right " );
	if( right[x] != -1 ) print( right[x] ); 
  printf( " up ");
}

void set_parent_child( int pa, int c ) {
  if ( pa == -1 ) return;
  if ( p[pa] == -1 ) root = c;
  else if ( pa == left[p[pa]] ) left[p[pa]] = c;
  else right[p[pa]] = c;
  if ( c != -1 ) p[c] = p[pa];
}

void fix_remove( int x ) {
}

int remove(int k) {
	int x = root;
	while( x != -1 && key[x] != k ) x = k < key[x] ? left[x] : right[x];
  printf( "find %d\n", x );
	if( x == -1 ) return -1;
  if( --mul[x] ) return x;
  printf( "haha\n" );

  // remove the node 
  // case 1 : both child exists
  int y, z;
  if ( left[x] != -1 && right[x] != -1 ) { 
    y = find_min( right[x] ); // find successor
    // 
    set_parent_child( y, right[y] );
    //
    key[x] = key[y];
    // copy the satellite data of y into x if neccessary
    free_node( y );
  } else if ( left[x] == -1 && right[x] == -1 ) {
    y = x;
    set_parent_child( y, -1 );
    free_node( x );
  } else {
    y = x;
    if ( left[y] != -1 ) {
      set_parent_child( y, left[y] );
    } else {
      set_parent_child( y, right[y] );
    }
    free_node( y );
  }


  if( color[y] == 0 ) 
    fix_remove(y);

  return y;
}

int main() {
	init();
	REP(i, 8) {
		printf("insert %d\n", i);
		insert(i);
	}
	printf("%d\n", n);


	printf("root = %d\n", root);
	print( root );
	puts("");

  REP(i, 8) {
    if ( i & 1 ) remove( i );
  }
  print( root );
  puts( "" );
	return 0;
}

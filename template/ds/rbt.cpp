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

int mul[N], key[N], left[N], right[N], color[N], p[N], root, n;

void init() {
	memset(left, -1, sizeof(left));
	memset(right, -1, sizeof(right));
	memset(p, -1, sizeof(right));
	memset(mul, 0, sizeof(mul));

	n = 0;
	root = -1;
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
}

int insert(int k) {
	// find
	int x, y;
	while ( x != -1 ) {
		y = x;
		if ( key[x] == k ) {
			mul[x]++;
			return mul[x];
		} else {
			x = key[x] < k ? right[x] : left[x];
		}
	}

	int z = n++;
	key[z] = k;
	left[z] = right[z] = -1;
	p[z] = y;
	color[z] = 1; 

	fix_insert(z);

	return 1;
}



int main() {
	return 0;
}

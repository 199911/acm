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
#include <map>
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

// Problem: SPOJ DQUERY
// Given Array A[300000], find the number of distinct element in A[i....j]

#define N 30005
#define LOGN 20

struct Node {
	int v, l, r, sz;
} T[N * LOGN];

int tree[N], a[N], n, sz;
map<int,int> last;

int build( int s, int t ) {
	if ( s > t ) return -1;

	int mid = ( s + t ) >> 1;
	int idx = sz++;
	int l = build( s, mid - 1 ), r = build( mid + 1, t );
	T[idx] = (Node){ mid, l, r, 0 };

	return idx;
}

int update( int idx, int x, int am ) {
	if ( idx < 0 ) return idx;

	int nid = sz++, nl = T[idx].l, nr = T[idx].r;

	if ( x < T[idx].v ) nl = update( T[idx].l, x, am );
	if ( x > T[idx].v ) nr = update( T[idx].r, x, am );

	T[nid] = (Node){ T[idx].v, nl, nr, T[idx].sz + am };

	return nid;
}

int query( int idx, int x ) {
	if ( idx == -1 ) return 0;
	if ( x < T[idx].v ) return query( T[idx].l, x ) + T[idx].sz - T[T[idx].l].sz;
	if ( x > T[idx].v ) return query( T[idx].r, x );
	return T[idx].sz - T[T[idx].l].sz;
}

int main() {
	scanf( "%d", &n );
	
	for( int i = 1; i <= n; i++ ) { 
		scanf( "%d", &a[i] );
	}

	sz = 0;
	tree[0] = build( 1, n );

	for( int i = 1; i <= n; i++ ) {
		int lst = last[a[i]];
		if ( lst ) {
			int tmp = update( tree[i - 1], lst, -1 );
			tree[i] = update( tmp, i, 1 );
			last[a[i]] = i;
		} else {
			tree[i] = update( tree[i - 1], i, 1 );
			last[a[i]] = i;
		}
	}

	int q;
	scanf( "%d", &q );
	while( q-- ) {
		int s, t;
		scanf( "%d%d", &s, &t );
		printf( "%d\n", query( tree[t], s ) );
	}

  return 0;
}

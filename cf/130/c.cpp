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

int adj[111][111], n, m;
int cnt1[111], d1[111];
int cnt2[111], d2[111];

void bfs1( int s ) {

	int q[111], qt, qh;
	qt = qh =0;
	q[qt++] = s;
	memset(d1, -1, sizeof(d1));
	memset(cnt1, 0, sizeof(cnt1));
	d1[s] = 0;
	cnt1[s] = 1;

	while(qt != qh) {
		int u = q[qh++];
		for(int v = 0; v < n; v++) {
			if ( adj[u][v] ) {
				if ( cnt1[v] == 0 ) {
					q[qt++] = v;
					d1[v] = d1[u] + 1;
				}
				if ( d1[v] == d1[u] + 1 ) cnt1[v] += cnt1[u];
			}
		}
	}
}

void bfs2( int s ) {
	int q[111], qt, qh;
	qt = qh =0;
	q[qt++] = s;
	memset(d2, -1, sizeof(d2));
	memset(cnt2, 0, sizeof(cnt2));
	d2[s] = 0;
	cnt2[s] = 1;

	while(qt != qh) {
		int u = q[qh++];
		for(int v = 0; v < n; v++) {
			if ( adj[u][v] ) {
				if ( cnt2[v] == 0 ) {
					q[qt++] = v;
					d2[v] = d2[u] + 1;
				}
				if ( d2[v] == d2[u] + 1 )
					cnt2[v] += cnt2[u];
			}
		}
	}
}



int main() {
	scanf("%d%d", &n, &m);
	memset(adj, 0, sizeof(adj));
	REP(i, m) {
		int a, b;
		scanf( "%d%d", &a, &b );
		a--; b--;
		adj[a][b] = adj[b][a] = 1;
	}

	bfs1(0);
	bfs2(n-1);

	int dd = d1[n-1];

	double ans = 1;
	for(int x = 1; x < n-1; x++) {
		if ( d1[x] + d2[x] == d1[n-1] ) {
			double cur = 2.0 * cnt2[x] * cnt1[x] / cnt1[n-1];
			if ( ans < cur ) ans = cur;
		}
	}

	printf("%f\n", ans);

	return 0;
}

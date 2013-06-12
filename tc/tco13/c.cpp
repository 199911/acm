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

#define N 2222
#define M 444444
#define INF (1<<29)

int n, m, en, s, t;
int hd[N], to[M], nt[M], cap[M], cost[M];

void init() {
	CLR( hd, -1 );
	CLR( nt, -1 );
	en = 0;
}

void add( int u, int v, int cp, int ct ) {
	to[en] = v; cap[en] = cp; cost[en] = ct; nt[en] = hd[u]; hd[u] = en++;
	to[en] = u; cap[en] = 0; cost[en] = -ct; nt[en] = hd[v]; hd[v] = en++;
}

int pv[N], pe[N], dist[N];

bool spfa( int s, int t ) {
	int q[N], qh, qt, inq[N];
	CLR( inq, 0 );
	CLR( pv, -1 );
	CLR( pe, -1 );
	fill( dist, dist + N, INF );
	qt = qh = 0;
	
	q[qt++] = s;
	inq[s] = 1;
	dist[s] = 0;

	while( qt != qh ) {
		int u = q[qh++]; qh %= N;
		inq[u] = 0;
		if ( u == t ) continue;
		for( int e = hd[u]; e != -1; e = nt[e] ) {
			if ( cap[e] == 0 ) continue;
			int v = to[e];
			if ( dist[v] > dist[u] + cost[e] ) {
				dist[v] = dist[u] + cost[e];
				pv[v] = u;
				pe[v] = e;
				if ( inq[v] == 0 ) {
					q[qt++] = v; qt %= N;
					inq[v] = 1;
				}
			}
		}
	}

	return dist[t] < INF;
}

int mincostflow() {
	int totc = 0;
	while( spfa( s, t ) ) {
		int cp = INF;
		for( int ptr = t; ptr != s; ptr = pv[ptr] ) cp = min( cp, cap[pe[ptr]] );
		for( int ptr = t; ptr != s; ptr = pv[ptr] ) {
			cap[pe[ptr]] -= cp;
			cap[pe[ptr] ^ 1] += cp;
		}
		totc += cp * dist[t];
	}
	return totc;
}

int H, W;

int idx( int r, int c ) {
	r = ( r + H ) % H;
	c = ( c + W ) % W;
	return r * W + c;
}

int dc[5] = { 0, 1, 0, -1 };
int dr[5] = { -1, 0, 1, 0 };
char dd[10] = "URDL";

struct DirectionBoard {
	int getMinimum( vector<string> board ) {
		H = board.size();
		W = board[0].length();
		init();
		n = H * W * 2 + 2;
		m = H * W * 6;
		s = 2 * H * W;
		t = 2 * H * W + 1;
		REP( i, H ) REP( j, W ) {
			add( s, idx( i, j ), 1, 0 );
			add( idx( i, j ) + H * W, t, 1, 0 );
			REP( k, 4 ) 
				add( idx( i, j ), idx( i + dr[k], j + dc[k] ) + H * W, 1, board[i][j] == dd[k] ? 0 : 1 );
		}

		return mincostflow();
	}
};

int main() {
  return 0;
}

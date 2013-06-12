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
#include <bitset>
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

#define N 1111
#define M 22222

struct MinCostFlowGraph {
	int hd[N], nt[M], to[M], cap[M], cost[M], n, en; 
	int dist[N], pv[N], pe[N], q[N], qt, qh, inq[N];

	MinCostFlowGraph() {}
	MinCostFlowGraph( int n ): n(n) {
		CLR( hd, -1 );
		CLR( nt, -1 );
		en = 0;
	}
	void add( int u, int v, int cp, int ct ) {
		to[en] = v; nt[en] = hd[u]; cap[en] = cp; cost[en] = ct; hd[u] = en++;
		to[en] = u; nt[en] = hd[v]; cap[en] = 0; cost[en] = -ct; hd[v] = en++;
	}

	bool spfa( int s, int t ) {
		qh = qt = 0;
		fill( dist, dist + N, INF );
		CLR( inq, 0 );
		CLR( pv, -1 );
		CLR( pe, -1 );
		q[qt++] = s; inq[s] = 1;
		dist[s] = 0;

		while( qt != qh ) {
			int u = q[qh++]; qh %= N;
			inq[u] = 0;
			if ( u == t ) continue;
			for( int e = hd[u]; e != -1; e = nt[e] ) {
				if ( cap[e] == 0 ) continue;
				int v = to[e];
				if ( dist[u] + cost[e] < dist[v] ) {
					dist[v] = dist[u] + cost[e];
					pv[v] = u; pe[v] = e;
					if ( !inq[v] ) {
						q[qt++] = v; qt %= N;
						inq[v] = 1;
					}
				}
			}
		}

		return dist[t] < INF;
	}

	int mincostflow( int s, int t, int f ) {
		int ret = 0;
		while( f > 0 ) {
			if ( spfa( s, t ) ) {
				int nf = f;
				for( int p = t; p != s; p = pv[p] ) nf = min( nf, cap[pe[p]] );
				for( int p = t; p != s; p = pv[p] ) {
					cap[pe[p]] -= nf;
					cap[pe[p] ^ 1] += nf;
				}
				f -= nf;
				ret += dist[t] * nf;
			} else return -1;
		}
		return ret;
	}
};

const char D[] = "UDRL";
const char DR[] = { -1, 1, 0, 0 };
const char DC[] = { 0, 0, 1, -1 };

struct DirectionBoard {
	int W, H;

	int idx( int r, int c ) {
		r = ( r + H ) % H;
		c = ( c + W ) % W;
		return r * W + c;
	}

	int getMinimum( vector<string> board ) {
		H = board.size();
		W = board[0].size();
		MinCostFlowGraph G( H * W * 2 + 2 );
		int s = H * W * 2, t = H * W * 2 + 1;
		for( int i = 0; i < H; i++ ) {
			for( int j = 0; j < W; j++ ) {
				G.add( s, idx( i, j ), 1, 0 );
				G.add( idx( i, j ) + H * W, t, 1, 0 );
				for( int k = 0; k < 4; k++ ) {
					G.add( idx( i, j ), idx( i + DR[k], j + DC[k] ) + H * W, 1, board[i][j] == D[k] ? 0 : 1 );
				}
			}
		}
		return G.mincostflow( s, t, H * W );
	}
};

int main() {
  return 0;
}

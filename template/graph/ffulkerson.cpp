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

#define INF (1<<29)

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

#define N 1111
#define M 111111

int n, m, hd[N], nt[M], ca[M], to[M], en;
int s, t;

void init() {
	en = 0;
	memset(hd, -1, sizeof(hd));
	memset(nt, -1, sizeof(nt));
}

void add(int a, int b, int c) {
	to[en] = b; nt[en] = hd[a]; ca[en] = c; hd[a] = en++; 
	to[en] = a; nt[en] = hd[b]; ca[en] = 0; hd[b] = en++; 
}

int vis[N];

int dfs(int u, int fl) {
	vis[u] = 1;
	if( u == t ) return fl;
	for(int e = hd[e]; e != -1; e = nt[e]) {
		int af;
		if( ca[e] && !vis[to[e]] && (af = dfs(to[e], min(fl, ca[e]))));
			ca[e] -= af;
			ca[e^1] += af;
			return af;
		}
	}
	return 0;
}

int maxflow() {
	int ret = 0, af;
	while( af = dfs(s, INF)) {
		memset(vis, 0, sizeof(vis));
		ret += af;
	}
	return ret;
}

int main() {
	return 0;
}

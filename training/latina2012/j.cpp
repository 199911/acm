#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 200005

int n, f[N], v[N], g[N], len[N], comp, st[N], top, num[N], cyc[N], dis[N], go[N], Q, a, b, AC;
int h[N], E, t, l[N], qd[N], qn[N], s[N][20];


void DFS(int x){
	v[x] = 1;
	st[top++] = x;
	int ok = 0;
	if (v[f[x]] == 1){
		g[x] = ++comp;
		len[comp] = 1;
		cyc[f[x]] = 1;
		num[f[x]] = 0;
		while (top > 0 && st[top-1] != f[x]){
			cyc[st[top-1]] = 1;
			num[st[top-1]] = len[comp];
			len[comp]++;
			top--;
		}
		ok = 1;
	}
	else if (v[f[x]] == 2) g[x] = g[f[x]];
	else DFS(f[x]);
	
	v[x] = 2;
	if (!ok) g[x] = g[f[x]];
}

void CALC(int x){
	dis[x] = 0;
	if (cyc[x]){
		dis[x] = 0;
		go[x] = num[x];
	}
	else{
		if (dis[f[x]] == -1) CALC(f[x]);
		dis[x] = dis[f[x]] + 1;
		go[x] = go[f[x]];
	}
}


void LCA_DFS(int x, int dep){
	h[x] = dep;
	v[++t] = x;
	f[x] = t;
	for (int k=l[x];k!=-1;k=qn[k]){
		if (cyc[qd[k]]) continue;
		LCA_DFS(qd[k], dep + 1);
		v[++t] = x;
	}
}

void Precompute(){
	FOE(i, 1, t) s[i][0] = h[v[i]];
	for (int i=1;(1<<i)<=t;i++)
	for (int j=1;j+(1<<i)-1<=t;j++)
		s[j][i] = min(s[j][i-1], s[j + (1<<(i-1))][i-1]);
}

int Query(int x, int y){
	if (f[x] > f[y]) swap(x, y);
	int l;
	for (l=0;(1<<(l+1))<=(f[y]-f[x]+1);l++);
	return min(s[f[x]][l], s[f[y]-(1<<l) + 1][l]);
}

void bd(int x, int y){
	qd[++E] = y;
	qn[E] = l[x];
	l[x] = E;
}

int main(){
	while (scanf("%d", &n) != EOF){
		
		CLR(l, -1);
		E = 0;
		
		FOE(i, 1, n){
			scanf("%d", &f[i]);
			bd(f[i], i);
		}	
		CLR(v, 0);
		CLR(g, 0);
		CLR(cyc, 0);
		
		comp = 0;
		
		FOE(i, 1, n){
			top = 0;
			if (!v[i]) DFS(i);
		}
		
		
		CLR(dis, -1);
		FOE(i, 1, n)
			if (dis[i] == -1) CALC(i);
			
		CLR(v, 0);
		t = 0;
		FOE(i, 1, n)
			if (cyc[i]) LCA_DFS(i, 0);
			
		//FOE(i, 1, n) printf("G[%d] = %d, cyc = %d, num = %d dis = %d, go = %d\n", i, g[i], cyc[i], num[i], dis[i], go[i]);
		//FOE(i, 1, comp) printf("LEN[%d] = %d\n", i, len[i]);
		
		//FOE(i, 1, n) printf("H[%d] = %d\n", i, h[i]);
		//FOE(i, 1, t) printf("%d%c", v[i], i==t?'\n':' ');
		Precompute();
		
		scanf("%d", &Q);
		while (Q--){
			scanf("%d%d", &a, &b);
			if (g[a] != g[b]) printf("-1\n");
			else {
				AC = 0;
				int mh = Query(a, b);
				AC = (h[a] - mh) + (h[b] - mh);
				if (mh == 0) AC += min(abs(go[a]-go[b]), len[g[a]]-abs(go[a]-go[b]));
				printf("%d\n", AC);
			}
		}
		
	}
	return 0;
}

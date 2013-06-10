#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 15005
#define M 2000005

int l[N], rl[N], qd[M], qn[M], rqd[M], rqn[M], E, top, scc[N], sccn = 0, tt;
int x[N], y[N], a, b, c, d, imposs, type[N], ok, f, q[N], stk[N], v[N];
int n, m, test, group[N];
vector <pair<int,int> > V[N];

int dx[4]={0, 1, 1, 0}, dy[4] = {0, 0, 1, 1};

void bd(int x, int y){
	qd[++E] = y;
	qn[E] = l[x];
	l[x] = E;
	
	rqd[E] = x;
	rqn[E] = l[y];
	rl[y] = E;
}

int Dis(int x1, int y1, int x2, int y2){
	return abs(x1 - x2) + abs(y1 - y2);
}

void DFS(int x){
	v[x] = 1;
	for (int k=l[x];k!=-1;k=qn[k])
		if (!v[qd[k]]) DFS(qd[k]);
	stk[--top] = x;
}

void RDFS(int x){
	v[x] = 1;
	scc[x] = sccn;
	for (int k=rl[x];k!=-1;k=rqn[k])
		if (!v[rqd[k]]) RDFS(rqd[k]);
}

void Travel(int x){
	int z = V[x].size();
	for (int k=0;k<z;k++)
		if (group[V[x][k].first] == -1){
			group[V[x][k].first] = (group[x] + V[x][k].second) % 2;
			Travel(V[x][k].first);
		}
	
}

int main() {
	scanf("%d", &test);
	while (test--){
		
		CLR(l, -1);
		CLR(rl, -1);
		E = 0;
		
		scanf("%d", &n);
		FOR(i, 0, n) V[i].clear();
		
		FOR(i, 0, n)
			scanf("%d%d", &x[i], &y[i]);
		scanf("%d", &m);
		FOR(i, 0, m){
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			FOR(j, 0, 4)
			FOR(k, 0, 4){
				d = Dis(x[a] + dx[j], y[a] + dy[j], x[b] + dx[k], y[b] + dy[k]);
				if ((d + c) % 2 != 0) continue;
				V[a].push_back(make_pair(b, (j - k + 4) % 2));
				V[b].push_back(make_pair(a, (j - k + 4) % 2));
				if (d != c){
					bd(a * 4 + j, b * 4 + (k + 2) % 4);
					bd(b * 4 + k, a * 4 + (j + 2) % 4);
				}
			}
		}
		
		imposs = 0;
		
		CLR(group, -1);
		FOR(i, 0, n)
			if (group[i] == -1){
				group[i] = 0;
				Travel(i);
			}
			
		//FOR(i, 0, n) printf("Group[%d] = %d\n", i, group[i]);
		
		FOR(i, 0, n){
			int z = V[i].size();
			FOR(j, 0, z)
				if (abs(group[V[i][j].first] - group[i]) != V[i][j].second) imposs = 1;
		}
		
		
		CLR(v, 0);
		//SCC
		
		top = n * 4;
		FOR(i, 0, n) FOR(j, 0, 4) if (!v[i * 4 + j]) DFS(i * 4 + j);
		
		CLR(v, 0);
		sccn = 0;
		FOR(i, 0, n * 4) if (!v[stk[i]]) {++sccn; RDFS(stk[i]);}
		
		/*
		FOR(i, 0, n)
			FOR(j, 0, 4)
				printf("%d%c", scc[i*4+j], j==3?'\n':' ');
		*/

		imposs = 0;
		FOR(i, 0, n){
			ok = 0;
			FOR(j, 0, 2)
				if (scc[i * 4 + j] != scc[i * 4 + j + 2]){		
					int fail = 0;
					FOR(k, 0, 4)
						if (k != j && k != j + 2)
							if (scc[i * 4 + k] == scc[i * 4 + j] || scc[i * 4 + k] == scc[i * 4 + j + 2]) fail = 1;
					if (!fail) ok = 1;
				}
					
			if (!ok) imposs = 1;
		}

		if (imposs) printf("impossible\n");
		else printf("possible\n");
	}
	return 0;
}

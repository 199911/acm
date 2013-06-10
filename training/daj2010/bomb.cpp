#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

#define N 3005
#define M 600005

int l[N], qd[M], qn[M], n, m;
int x[N], y[N], a, b, c, v[N], siz, E, test, fail;

void bd(int x, int y){
	qd[++E] = y;
	qn[E] = x;
	l[x] = E;
}

void DFS(int x){
	v[x] = 1;
	siz++;
	for (int k=l[x];k!=-1;k=qn[k])
		if (!v[qd[k]]) DFS(qd[k]);
}

int main() {
	scanf("%d", &test);
	while (test--){
		
		CLR(l, -1); E = 0;
		scanf("%d", &n);
		FOR(i, 0, n)
			scanf("%d%d", &x[i], &y[i]);
		scanf("%d", &m);
		
		FOR(i, 0, m){
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			bd(a, b);
			bd(b, a);
		}
		
		CLR(v, 0);
		fail = 0;
		
		FOR(i, 0, n)
			if (!v[i]){
				siz = 0;
				DFS(i);
				if (siz != n) fail = 1;
			}
		
		if (fail) while (1);
		else printf("HAHA\n");
		
	}
	return 0;
}

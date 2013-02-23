#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 500005

LL s[N], sum[N], cover[N], y, z;
char cmd[30];
int tmp, n, Q, t, siz[N], st[N], ed[N], E, l[N], qd[N], qn[N], p[N];
int L[N], R[N], w[N], x;

void bd(int x, int y){
	qd[++E] = y;
	qn[E] = l[x];
	l[x] = E;
}

void DFS(int x){
	siz[x] = 1;
	st[x] = ++t;
	p[t] = x;
	for (int k=l[x];k!=-1;k=qn[k]){
		DFS(qd[k]);
		siz[x] += siz[qd[k]];
	}
	ed[x] = t;
}

void Init(int x, int l, int r){
	sum[x] = 0;
	cover[x] = 0;
	L[x] = l;
	R[x] = r;
	if (l != r){
		int k = (l + r) >> 1;
		Init(x * 2, l, k);
		Init(x * 2 + 1, k + 1, r);
		sum[x] = sum[x * 2] + sum[x * 2 + 1];
	}
	else sum[x] = s[p[l]];
}

void Update(int x, LL v){
	cover[x] += v;
	sum[x] += (R[x] - L[x] + 1LL) * v;
}

void Update(int x, int l, int r, LL v){
	if (R[x] < l || r < L[x]) return;
	if (l <= L[x] && R[x] <= r) Update(x, v);
	else {
		if (cover[x] != 0){
			Update(x * 2, cover[x]);
			Update(x * 2 + 1, cover[x]);
			cover[x] = 0;
		}
		Update(x * 2, l, r, v);
		Update(x * 2 + 1, l, r, v);
		sum[x] = sum[x * 2] + sum[x * 2 + 1];
	}
}

LL Query(int x, int l, int r){
	if (R[x] < l || r < L[x]) return 0;
	if (l <= L[x] && R[x] <= r) return sum[x];
	else {
		if (cover[x] != 0){
			Update(x * 2, cover[x]);
			Update(x * 2 + 1, cover[x]);
			cover[x] = 0;
		}
		LL A = Query(x * 2, l, r);
		LL B = Query(x * 2 + 1, l, r);
		sum[x] = sum[x * 2] + sum[x * 2 + 1];
		return A + B;
	}
}

int main() {
	scanf("%d%d%lld", &n, &Q, &s[0]);
	CLR(l, -1); E = 0;
	
	FOR(i, 1, n){
		scanf("%d%lld", &tmp, &s[i]);
		bd(tmp, i);
	}
	
	t = 0;
	DFS(0);
	
	//FOR(i, 0, n) printf(" NODE %d, ST = %d, ED = %d, SIZ = %d\n", i, st[i], ed[i], siz[i]);
	//FOE(i, 1, t) printf(" p[%d] = %d\n", i, p[i]);
	
	Init(1, 1, t);
	//printf(" INIT\n");
	
	while (Q--){
		scanf("%s%d%lld%lld", cmd, &x, &y, &z);
		LL total;
		if (cmd[0] == 'e'){
			total = Query(1, st[x], st[x]);
			if (total < y) Update(1, st[x], st[x], z);
		}
		else if (cmd[0] == 'd'){
			LL total = Query(1, st[x], ed[x]);
			if (total < (LL)(siz[x]) * y) Update(1, st[x], ed[x], z);
		}
		//printf(" OK \n");
		//printf(" HIHI\n");
		//FOR(i, 0, n) printf("   Node [%d] = %lld\n", i, Query(1, st[i], st[i]));
	}
	
	
	FOR(i, 0, n) printf("%lld\n", Query(1, st[i], st[i]));
	//FOR(i, 0, n) printf("%lld\n", Query(1, st[i], st[i]));
	
	return 0;
}

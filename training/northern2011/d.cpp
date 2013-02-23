#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 55
#define M 2005

int n, m, a, b, qd[M], qn[M], l[N], v[N], ret[N], AC = 0, mx, fail, ok, E, q[N];
int d, cp;

void bd(int x, int y){
	qd[++E] = y;
	qn[E] = l[x];
	l[x] = E;
}

int main() {
	scanf("%d%d", &m, &n);
	CLR(l, 0); E = 0;
	while (m--){
		scanf("%d%d", &a, &b);
		bd(a, b);
		bd(b, a);
	}
	
	fail = 0;
	cp = 0;
	CLR(v, 0);
	
	FOE(x, 1, n){
		if (v[x]) continue;
		cp++;
		q[0] = x;
		if (cp == 1) v[x] = 1;
		else v[x] = 50;
		
		if (cp == 1) d = 1;
		else d = -1;
		
		for (int i=0,j=0;i<=j;i++)
			for (int k=l[q[i]];k;k=qn[k]){
				if (v[qd[k]] == 0)
					v[q[++j] = qd[k]] = v[q[i]] + d;
				else if (abs(v[qd[k]] - v[q[i]]) != 1) fail = 1;
			}
		if (fail) break;	
	}
	
	if (fail) printf("-1\n");
	else {
		
		if (cp == 1){
			
			FOE(x, 1, n){
				CLR(v, 0);
				int mx = 0;
				v[q[0] = x] = 1;
				for (int i=0,j=0;i<=j;i++)
					for (int k=l[q[i]];k;k=qn[k])
						if (v[qd[k]] == 0){
							v[q[++j] = qd[k]] = v[q[i]] + 1;
							mx = max(mx, v[qd[k]]);
						}
				if (mx > AC){
					AC = mx;
					FOE(i, 1, n) ret[i] = v[i];
				}
			}
			printf("%d\n", AC - 1);
			FOE(i, 1, n) printf("%d%c", ret[i], i==n?'\n':' ');
		}
		if (cp > 1){
			printf("%d\n", 49);
			FOE(i, 1, n) printf("%d%c", v[i], i==n?'\n':' ');
		}
	}
	
	
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 
#define MOD 9999991

#define N 25

int test, n, a[(1<<22)], siz[(1<<22)], cur, x, b[N];
LL C[N][N];

LL f(int x){
	if (siz[x] == 0) return 1;
	LL R = C[siz[x * 2] + siz[x * 2 + 1]][siz[x * 2]];
	R = (R * f(x * 2)) % MOD;
	R = (R * f(x * 2 + 1)) % MOD;
	return R;
}

int main() {
	scanf("%d", &test);
	
	FOE(i, 0, 20)
	FOE(j, 0, i){
		if (j == 0 || j == i) C[i][j] = 1;
		else C[i][j] = C[i-1][j-1] + C[i-1][j];
		C[i][j] %= MOD;
	}
	
	CLR(siz, 0);
	CLR(a, 0);
	
	while (test--){
		scanf("%d", &n);
		FOE(i, 1, n){
			scanf("%d", &x);
			b[i] = x;
			cur = 1;
			while (a[cur] != 0){
				siz[cur]++;
				if (x > a[cur]) cur = cur * 2 + 1;
				else cur = cur * 2;
			}
			a[cur] = x;
			siz[cur]++;
		}
		printf("%d\n", (int)f(1));
		
		for (int i=n;i>=1;i--){
			cur = 1;
			while (a[cur] != b[i]){
				if (b[i] > a[cur]) cur = cur * 2 + 1;
				else cur = cur * 2;
			}
			a[cur] = 0;
			siz[cur] = 0;
		}
	}
	return 0;
}

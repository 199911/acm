#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#define FOR(i,s,e) for (int i=(s); i<(e); i++)
#define FOE(i,s,e) for (int i=(s); i<=(e); i++)
#define FOD(i,s,e) for (int i=(s)-1; i>=(e); i--)
#define CLR(a,x) memset(a, x, sizeof(a))
#define EXP(i,l) for (int i=(l); i; i=qn[i])
#define LLD long long
#define N 10005
using namespace std;

LLD MOD = 1000002013;

LLD Cost(int d, int n){
	return (n * 1LL * (d + 1LL) - d * 1LL * (d + 1LL) / 2) % MOD;
}

int n, m;
int xx[N], yy[N], ww[N];
int dis[N];
LLD a[N], b[N];
LLD d1[N], d2[N];

void solve(int tc){
	printf("Case #%d: ", tc);
	scanf("%d%d", &n, &m);
	
	LLD ret = 0;
	int cnt = 0;
	CLR(a, 0);
	CLR(b, 0);

	FOR(i,0,m){
		scanf("%d%d%d", &xx[i], &yy[i], &ww[i]);
		ret = (ret + Cost(yy[i] - xx[i], n) * ww[i]) % MOD;
		dis[cnt++] = xx[i];
		dis[cnt++] = yy[i];
	}
	sort(dis, dis + cnt);
	cnt = unique(dis, dis + cnt) - dis;
	
	FOR(i,0,m){
		int x, y, w = ww[i];
		x = lower_bound(dis, dis + cnt, xx[i]) - dis;
		y = lower_bound(dis, dis + cnt, yy[i]) - dis;
		a[x] += w;
		b[y] += w;
	}

	int size = 0;
	int prev = dis[0];
	FOR(i,0,cnt){
		FOR(j,0,size) d1[j] += dis[i] - prev;
		d1[size] = 0;
		d2[size] = a[i];
		++size;
		
		FOD(j,size,0){
			LLD t = min(d2[j], b[i]);
			d2[j] -= t;
			b[i] -= t;
			ret = (ret - t * Cost(d1[j], n)) % MOD;
			ret = (ret + MOD) % MOD;
		}
		
		prev = dis[i];
	}
	printf("%lld\n", ret);
}

int main(){
	int tc;
	scanf("%d", &tc);
	FOE(i,1,tc) solve(i);
	return 0;
}

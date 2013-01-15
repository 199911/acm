#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int n,k;
int d[1005],w;
LL sumw[1005],sump[1005],dp[1005][1005],inf;

int main() {
	inf = (1LL<<60);
	while (scanf("%d%d",&n,&k) == 2) {
		sumw[0] = 0;
		sump[0] = 0;
		for (int i=1; i<=n; i++) {
			scanf("%d%d",&d[i],&w);
			sumw[i] = sumw[i-1] + w;
			sump[i] = sump[i-1] + d[i]*1LL*w;
		}	
		dp[0][0] = 0;
		for (int i=1; i<=n; i++) dp[i][0] = inf;
		for (int i=1; i<=n; i++) {
			int x = 0;
			for (int j=1; j<=k; j++) {
				dp[i][j] = inf;
				//x = 0;
				for ( ; x<i; x++) {
					//printf("%d: %I64d+%I64d-%I64d\n",x,dp[x][j-1],d[i]*(sumw[i]-sumw[x]),(sump[i]-sump[x]));
					if (dp[x][j-1] + d[i]*(sumw[i]-sumw[x]) - (sump[i]-sump[x]) < dp[i][j]) {
						dp[i][j] = dp[x][j-1] + d[i]*(sumw[i]-sumw[x]) - (sump[i]-sump[x]);
					}
					else {
						break;
					}
				}
				x--;
				//printf("%d,%d = %I64d %d\n",i,j,dp[i][j],x);
			}	
		}
		printf("%lld\n",dp[n][k]);
	}
  return 0;
}

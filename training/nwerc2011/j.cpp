#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define FOE(i,a,b) for(int i = a; i <= b; i++)
#define REP(i,n) FOR(i,0,n)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

#define N 1005
#define L 30
#define INF (1e30)

double dp[N][65], AC;
char start[L], end[L], fu[L], fv[L], s[N][L];
int stmin[N], len[N], p[N], d[N], st, ed, u, v, to[N], TC, n, m;
vector <int> E[N];


double Expect(int x, int t){

  if (x == ed) dp[x][t] = 0;
  if (fabs(dp[x][t] - INF) > 1e-3) return dp[x][t];

  FOR(i, 0, E[x].size()){
    int k = E[x][i], Q;
    double S;
    Q = stmin[k] - t;
    if (Q < 0) Q += 60;
    S = Q;

    S += (1 - p[k]/100.0) * (Expect(to[k], (Q + len[k]) % 60) + len[k]);
    FOE(j, 1, d[k])
      S += p[k]/100.0 * 1.0/(d[k]) * (Expect(to[k], (Q + len[k] + j)%60) + len[k] + j);

    dp[x][t] = min(dp[x][t], S);
  }
  printf(" E( %d %d ) = %f\n", x, t, dp[x][t]);
  return dp[x][t];
}

int main(){
  scanf("%d", &TC);

  while (TC--){

    FOR(i, 0, N) E[i].clear();

    scanf("%s%s", start, end);
    n = 0;
    scanf("%d", &m);
    FOR(i, 0, m){
      scanf("%s%s%d%d%d%d", fu, fv, &stmin[i], &len[i], &p[i], &d[i]);
      u = v = -1;
      FOR(j, 0, n)
        if (strcmp(fu, s[j]) == 0) u = j;
      if (u == -1)
        memcpy(s[u = n++], fu, sizeof(fu));

      FOR(j, 0, n)
        if (strcmp(fv, s[j]) == 0) v = j;
      if (v == -1) memcpy(s[v = n++], fv, sizeof(fv));

      to[i] = v;

      E[u].push_back(i);
      printf(" %d -> %d\n", u, v);
    }

    st = ed = -1;
    FOR(i, 0, n){
      if (strcmp(start, s[i]) == 0) st = i;
      if (strcmp(end, s[i]) == 0) ed = i;
    }

    if (st == -1 || ed == -1){
      printf("IMPOSSIBLE\n");
      continue;
    }

    printf("# %d -> %d\n", st, ed);

    FOR(i, 0, n) FOR(j, 0, 60) dp[i][j] = INF;

    AC = INF;
    FOR(i, 0, 60) AC = min(AC, Expect(st, i));

    if (fabs(AC - INF) < 1e-3) printf("IMPOSSIBLE\n");
    else printf("%f\n", AC);

  }
  return 0;
}


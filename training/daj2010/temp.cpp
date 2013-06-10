#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 15005
#define M 2000005

int L[N], QD[M], QL[M], QN[M], l[N], qst[M], qed[M], qn[M], E, EE, ct, scc[N], sccn = 0, tt;
int x[N], y[N], tx, ty, td, imposs, type[N], ok, f, q[N], stk[N], v1[N], v2[N];
int n, m, test;

int dx[4]={0, 1, 1, 0}, dy[4] = {0, 0, 1, 1};

int Dis(int x1, int y1, int x2, int y2){
  return abs(x1 - x2) + abs(y1 - y2);
}

void BD(int x, int y, int d){
  QD[EE] = y;
  QN[EE] = L[x];
  QL[EE] = d;
  L[x] = EE++;
}

void bd(int x, int y){
  qst[E] = x;
  qed[E] = y;
  qn[E] = l[x];
  l[x] = E++;
}

int Build_Graph(int st){
  CLR(l, -1); E = 0;
  q[0] = st;

  int t, d1, d2, cnt = 1;

  for (int i=0,j=0;i<=j;i++)
    for (int k=L[q[i]];k!=-1;k=QN[k]){
      //printf("Q[ ] =  %d\n", q[i]);
      if ((Dis(x[q[i]] + dx[type[q[i]]], y[q[i]] + dy[type[q[i]]], x[QD[k]], y[QD[k]]) + QL[k]) % 2 == 0) t = 0;
      else t = 1;

      if (type[QD[k]] == -1){
        cnt++;
        type[QD[k]] = t;
        q[++j] = QD[k];
      }
      else if (type[QD[k]] != t) return -1;

      FOR(p1, 0, 2)
        FOR(p2, 0, 2){
          d1 = p1 * 2 + type[q[i]];
          d2 = p2 * 2 + type[QD[k]];
          if (Dis(x[q[i]] + dx[d1], y[q[i]] + dy[d1], x[QD[k]] + dx[d2], y[QD[k]] + dy[d2]) != QL[k]){
            printf(" [%d %d] -> [%d %d]\n", q[i], d1, QD[k], (d2 + 2) % 4);
            printf(" [%d %d] -> [%d %d]\n", QD[k], d2, q[i], (d1 + 2) % 4);
            bd(4 * q[i] + d1, 4 * QD[k] + (d2 + 2) % 4);
            bd(4 * QD[k] + d2, 4 * q[i] + (d1 + 2) % 4);
          }

        }
    }
  /*  
      FOR(i, 0, 4 * n)
      for (int k=l[i];k!=-1;k=qn[k])
      printf("[%d %d] -> [%d %d]\n", i/4, i%4, qed[k]/4, qed[k]%4);
   */
  FOR(i, 0, n) printf("type[%d] = %d\n", i, type[i]);

  return cnt;
}

void DFS(int x){
  v1[x] = 1;
  for (int k=l[x];k!=-1;k=qn[k])
    if (!v1[qed[k]]) DFS(qed[k]);
  stk[--ct] = x;
}

void RDFS(int x){
  v2[x] = 1;
  scc[x] = sccn;
  for (int k=l[x];k!=-1;k=qn[k])
    if (!v2[qed[k]]) RDFS(qed[k]);
}

void SCC(int st, int total){
  ct = total * 2;

  FOR(i, 0, total){
    int x = q[i] * 4 + type[q[i]];
    if (!v1[x]) DFS(x);
    if (!v1[x + 2]) DFS(x + 2);
  }

  FOR(i, 0, total) l[q[i] * 4 + type[q[i]]] = l[q[i] * 4 + type[q[i]] + 2] = -1;

  FOR(i, 0, E) bd(qed[i], qst[i]);

  FOR(i, 0, ct)
    if (!v2[stk[i]]){
      ++sccn;
      RDFS(stk[i]);
    } 
}

int main() {
  scanf("%d", &test);
  while (test--){

    CLR(L, -1); EE = 0;

    scanf("%d", &n);
    FOR(i, 0, n)
      scanf("%d%d", &x[i], &y[i]);
    scanf("%d", &m);
    FOR(i, 0, m){
      scanf("%d%d%d", &tx, &ty, &td);
      tx--; ty--;
      BD(tx, ty, td);
      BD(ty, tx, td);
    }

    imposs = 0;
    CLR(type, -1);
    CLR(v1, 0);
    CLR(v2, 0);

    FOR(i, 0, n)
      if (type[i] == -1){
        f = 0;
        FOR(j, 0, 2){
          type[i] = j;
          tt = Build_Graph(i);
          if (tt == -1) continue;

          SCC(i, tt);

          ok = 1;
          FOR(k, 0, tt){
            printf("type[%d] = %d\n", q[k], type[q[k]]);
            printf("   scc %d - %d\n", scc[4 * q[k] + type[q[k]]], scc[4 * q[k] + 2 + type[q[k]]]);
            if (scc[4 * q[k] + type[q[k]]] == scc[4 * q[k] + type[q[k]] + 2]) ok = 0;
          }
          if (ok) f = 1;
          //break;
        }
        if (!f) imposs = 1;
      }

    if (!imposs) printf("possible\n");
    else printf("impossible\n");

  }
  return 0;
}


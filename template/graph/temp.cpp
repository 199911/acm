int Min_Cost_Flow(){
  FOE(i, S, T){ D[i] = INF; u[i] = 0;}
  D[S] = 0; q[0] = S; int siz = 1, tl = 0;
  for (int i=0;siz;i++){
    siz--; if (i == V) i = 0;
    u[q[i]] = 0;
    for (int k=l[q[i]];k!=-1;k=qn[k]){
      if (qc[k] <= 0) continue;
      if (D[q[i]] + qw[k] < D[qd[k]]){
        D[qd[k]] = D[q[i]] + qw[k];
        par[qd[k]] = q[i];
        f[qd[k]] = k;
        if (!u[qd[k]]){
          ++siz;
          if (++tl == V) tl = 0;
          q[tl] = qd[k];
          u[qd[k]] = 1;
        }
      }
    }
  }
  if (D[T] == INF) return 0;
  else {
    cost += D[T];
    for (int i=T;i!=S;i=par[i]) qc[f[i]]--, qc[f[i]^1]++;
    return 1;
  }
}
//  S = Source, T = Sink, V = # of vertex
cost = 0;
while (Min_Cost_Flow()) Flow++;

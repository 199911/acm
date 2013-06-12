int cur[N], n, m, hd[N], nxt[M], to[M], end, c[M]; // graph structure
int d[N];   // traversal
int s, t;             // source and sink

void init(){
  for(int i=0; i<n; i++) hd[i]=-1;
  for(int i=0; i<m; i++) nxt[i]=-1;
  end=0;
}

void add(int u, int v, int ca, int revc){
  int tmp=hd[u];
  hd[u]=end++; nxt[hd[u]]=tmp; to[hd[u]]=v; c[hd[u]]=ca;
  tmp=hd[v];
  hd[v]=end++; nxt[hd[v]]=tmp; to[hd[v]]=u; c[hd[v]]=revc;
}

bool bfs(){
  int q[N], f=0, r=0;
  for(int i=0; i<n; i++) d[i]=-1;
  q[r++]=s;
  d[s]=0;
  while(f<r){
    int w=q[f++];
    for(int p=hd[w]; p!=-1; p=nxt[p])
      if(c[p]>0&&d[to[p]]==-1){
        q[r++]=to[p];
        d[to[p]]=d[w]+1;
      } 
  }
  return d[t]!=-1;
}

int dfs(int w, int fl){
  if(w==t) return fl;
  for(int &p=cur[w]; p!=-1; p=nxt[p]){
    int v=to[p], nf;
    if(c[p]>0 && d[v]==d[w]+1 && (nf=dfs(v, min(c[p], fl)))){
      c[p]-=nf; c[p^1]+=nf;
      return nf;
    }
  }
  return 0;
}

int dinic(){
  int flow=0, nf;
  while(bfs()){
    copy(hd, hd+n, cur);
    while(nf=dfs(s, INF)){
      flow+=nf;
    }
  }
  return flow;
}


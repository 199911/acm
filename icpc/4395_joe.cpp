// By Joe     @ July, 2010
// Use sweep line algorithm to build tree
// then do DP on tree
#include<stdio.h>
#include<math.h>
#include<map>
#include<string.h>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
#define EPS 1e-9
#define LL long long
#define INF 2000000000000ll

LL abs64(LL x){ return (x>=0)?x:(-x); }

struct Point{
  LL x,y;
  Point(){}
  Point(LL x,LL y):x(x),y(y){}
};

int n,K;
LL r[50010],w[50010];
Point c[50010];

vector<pair<int,int> > b;

int now;

struct Evt{
  int id;
  bool open;
  Evt(){}
  Evt(int id,bool open):id(id),open(open){}

  double getx(int now)const{
    LL rr = r[id];
    LL d = abs64(c[id].y-now);
    double k = sqrt(rr*rr-d*d);
    if (open)
      return c[id].x-k;
    return c[id].x+k;
  }

  bool operator < (const Evt &e)const{
    double x1=getx(now), x2=e.getx(now);
    return x1<x2-EPS || (fabs(x1-x2)<EPS && open>e.open);
  }
};

map<Evt,int> M;
typedef map<Evt,int>::iterator MI;

int nt[100010],to[100010],st[100010], E;
void addedge(int x,int y){ nt[E]=st[x]; to[E]=y; st[x]=E++; }

LL ans=0;
vector<pair<LL,LL> > f[50010];
vector<pair<LL,LL> > fx;
// fx[m].first max
// fx[m].second min
void dfs(int x){

  int m = 0;
  for (int i=st[x]; i!=-1; i=nt[i]){
    dfs(to[i]);
    m = max(m,(int)f[to[i]].size());
  }
  if (m > K) m = K;

  fx.clear();
  for (int i=0; i<=m; i++){
    if (x==n) fx.push_back(make_pair(-INF, INF));
    else fx.push_back(make_pair(w[x],w[x]));
  }

  for (int i=st[x]; i!=-1; i=nt[i]){
    int u=to[i];
    for (int j=1; j<=min(m,(int)f[u].size()); j++){
      if (f[u][j-1].first > fx[j].first) fx[j].first = f[u][j-1].first;
      if (f[u][j-1].second < fx[j].second) fx[j].second = f[u][j-1].second;
    }
  }

  for (int i=0; i<m; i++){
    if (fx[i].first > fx[i+1].first) fx[i+1].first = fx[i].first;
    if (fx[i].second < fx[i+1].second) fx[i+1].second = fx[i].second;
  }

  for (int i=st[x]; i!=-1; i=nt[i]) f[to[i]].clear();

  for (int i=0; i<=m; i++){
    ans = max(ans, (LL)fx[i].first - (LL)fx[min(m,K-i)].second);
  }
  f[x] = fx;
}

int main(){
  int ca; scanf("%d",&ca);
  for (int tt=1; tt<=ca; tt++){
    scanf("%d%d",&n,&K);
    b.clear();
    for (int i=0; i<n; i++){
      scanf("%lld%lld%lld%lld",&c[i].x,&c[i].y,&r[i],&w[i]);
      b.push_back(make_pair(c[i].y-r[i], i));
      b.push_back(make_pair(c[i].y+r[i], i+n));
    }
    sort(b.begin(),b.end());

    memset(st,-1,sizeof(st));
    E=0;

    M.clear();
    for (int i=0; i<b.size(); i++){
      now = b[i].first;
      int id = b[i].second%n;
      int op = b[i].second/n;
      Evt e1 = Evt(id, true);
      Evt e2 = Evt(id, false);
      if (op == 0){
        MI p = M.lower_bound(e1);
        int par = n;
        if (p==M.end()) par=n;
        else if (!(p->first).open) par = (p->first).id;
        else par = p->second;

        M[e1]=M[e2]=par;
        addedge(par,id);

      }else{
        M.erase(e1);
        M.erase(e2);
      }
    }
    ans = 0;
    for (int i=0; i<=n; i++) f[i].clear();
    dfs(n);
    printf("Case %d: %lld\n",tt,ans);
  }
  return 0;
}



// By Kn    31/12/2010
// Brute force search
// (Do put your code here if you find any poly-time algo)
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
using namespace std;
typedef long long LL;
#define FOR(i,s,e) for(int i=(s);i<(int)(e);i++)
#define FOE(i,s,e) for(int i=(s);i<=(int)(e);i++)
#define CLR(s) memset(s,0,sizeof(s))

const int N=3010, M=300010*2;
short bo[N][N];	// each bit in [i][j] represent validity of each of the 4 x 4 arrangement, for node pair(i,j)
int x[N],y[N];
int n;
int hd[N],v[M],ne[M],m;
int well[N],mea[M],waa[M],mmm; // graph holding back edges
void add(int x,int y){
    v[++m]=y, ne[m]=hd[x], hd[x]=m;
}
void plu(int x,int y){
    mea[++mmm]=y, waa[mmm]=well[x], well[x]=mmm;
}
int dx[]={0,0,1,1};
int dy[]={0,1,0,1};
int Abs(int x) { return x<0?-x:x; }
int rem;
int a[N];
bool vis[N];
int birth[N];
bool ok;

int term[N], dep;

// Brute force search to check validity
void dfs(int k) {
    if (k==dep || ok){ ok=1; return; }
    int u=term[k];
    FOR(r,0,4) {
        a[u]=r;
        bool valid=1;
        for(int j=well[u];valid&&j;j=waa[j]) {
            int x=mea[j];
            valid = bo[u][x]&(1<<(4*r+a[x]));
        }
        if (!valid) continue;
        dfs(k+1);
    }
}

// Find connected components
int go(int k) {
    if(vis[k]) return 0;
    term[dep++]=k;
    birth[k]=dep;
    vis[k]=1;
    int ans=1;
    for(int j=hd[k];j;j=ne[j]) {
        int res=go(v[j]);
        if (res)
        ans+=res;
        else if(birth[k]>birth[v[j]])
        plu(k,v[j]);	// back edges
    }
    return ans;
}

int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        scanf("%d",&n);
        FOE(i,1,n) scanf("%d%d",x+i,y+i);
        int k;
        scanf("%d",&k);
        FOE(i,1,n) hd[i]=0;
        m=0;
        FOE(r,1,k) {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            int ii,jj,cc=0;
            bo[a][b]=bo[b][a]=0;
            FOR(i,0,4) FOR(j,0,4) {
                int ddx=Abs((x[a]+dx[i])-(x[b]+dx[j]));
                int ddy=Abs((y[a]+dy[i])-(y[b]+dy[j]));
                if (ddx+ddy==c) {
                    bo[a][b] |= 1<<(i*4+j);
                    bo[b][a] |= 1<<(j*4+i);
                    // Attempt to opt, turn out no need
                    // if (++cc==1) ii=i, jj=j;
                }
            }
            add(a,b);
            add(b,a);
        }
        FOE(i,1,n) vis[i]=0,well[i]=0;
        mmm=0;
        ok=1;
        int lop=0;
        FOE(i,1,n) if(!vis[i] && ok) {
            dep=ok=0;
            go(i);
            dfs(0);
            //			while(++lop>1);	// Test assumption of "connectdness"
        }
        puts(ok?"possible":"impossible");
    }
    return 0;
}

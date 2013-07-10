#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

#define N 1111

int g[N][N], v[N], f[N], u[N], q[N], n;

int dmst( int r ) {
  int S = 0, x, y, w, t, e = 0; 

  memset(v, 0, sizeof(v)); 
  while (!e){
    e = 1; 
    for (int i=1; i<=n; i++){
      if (i==r || v[i]) continue; 
      f[i] = 0; 
      for (int j=1; j<=n; j++){
        if (i==j || v[j]) continue; 
        if (!f[i] || g[j][i]<g[f[i]][i]) f[i] = j; 
      }
    }

    memset(u, 0, sizeof(u)); 
    for (int i=1; i<=n; i++){
      if (v[i] || u[i] || i==r) continue; 
      x = i; 
      t = 0; 
      while (x>0 && !u[x]){
        u[q[++t]=x] = 1; 
        x = f[x]; 
      }
      w = 1; 
      while (w<=t && q[w]!=x) w++; 
      if (w == t+1) continue;
      e = 0; 
      for (int j=w; j<=t; j++){
        S += g[f[q[j]]][q[j]]; 
        if (j!=w) v[q[j]] = 1; 
      }
      for (int j=w; j<=t; j++){
        for (int k=1; k<=n; k++){
          if (v[k] || k==x) continue; 
          g[x][k] = min(g[x][k], g[q[j]][k]); 
          g[k][x] = min(g[k][x], g[k][q[j]] - g[f[q[j]]][q[j]]); 
        }
      }
    }
  }

  for (int i=1; i<=n; i++){
    if (!v[i] && i!=r) S += g[f[i]][i]; 
  }
  return S; 

}

int main() {
  return 0;
}

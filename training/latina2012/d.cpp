#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int n, m, b[100], AC, x, ok;

int main() {
  while (scanf("%d%d", &n, &m) != EOF){
    AC = 0;
    for (int i=n;i<=m;i++){
      x = i;
      CLR(b, 0);
      while (x){
        b[x%10]++;
        x/=10;
      }
      ok = 1;
      for (int j=0;j<10;j++) if (b[j] >= 2) ok = 0;
      AC += ok;
    }
    printf("%d\n", AC);
  }
  return 0;
}

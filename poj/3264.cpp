#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int q[50009][22], Q[50009][22], n, k, lg[50009];

int main(){
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; i++){
    scanf("%d", &q[i][0]);
    Q[i][0] = q[i][0];
  }

  memset(lg, 0, sizeof(lg));
  lg[0] = 0;
  for(int i = 0; 1 << i < 50009; i++) {
    lg[1<<i] = i;
  }

  for(int i = 1; i < 50009; i++) {
    if(lg[i] == 0) lg[i] = lg[i-1];
  }

  for(int l = 1, x = 2; x <= n; l++, x <<= 1 ) {
    for(int i = 0; i < n; i++) {
      Q[i][l] = max(Q[i][l-1], Q[min(n-1, i+(1<<(l-1)))][l-1]);
      q[i][l] = min(q[i][l-1], q[min(n-1, i+(1<<(l-1)))][l-1]);
//      printf("%d %d %d %d\n", i, l, q[i][l], Q[i][l]);
    }
  }

  for(int i = 0; i < k; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    int l = b - a + 1;
//    printf("%d\n", b - (1<<lg[l]));
    int mx = max( Q[a][lg[l]], Q[b-(1<<lg[l])+1][lg[l]] );
    int mn = min( q[a][lg[l]], q[b-(1<<lg[l])+1][lg[l]] );
//    printf("%d %d\n", mx, mn);
    printf("%d\n", mx - mn);
  }
  return 0;
}

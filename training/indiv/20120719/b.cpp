#include <cstdio>

int main(){
  char st[111];
  int t, n, k;

  while( scanf("%d%d", &n, &k), n || k ) {
    k *= 3;
    for(int i = 0; i < n; i++) {
      scanf("%s%d", st, &t);
      k -= t;
    }
    printf("%d\n", k);
  }

  return 0;
}

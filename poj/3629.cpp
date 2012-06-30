#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define K 100010

int n, k, p, cd[K], nn = 0, dl[K], left, nt[K], pr[K];

int main(){
  int ptr = 0, d = 0;
  scanf("%d%d%d", &n, &k, &p);
  left = k;
  memset(dl, 0, sizeof(dl));
  for(int i = 0; i < k; i++) {
    nt[i] = ( i + 1 ) % k;
    pr[i] = ( i + k - 1) % k;
  }
  while(left) {
    if(d == n - 1) cd[nn++] = ptr;
    d++; d %= n;
    dl[ptr] = 1;
    nt[pr[ptr]] = nt[ptr];
    pr[nt[ptr]] = pr[ptr];
    left--;
    if(!left) break;
    ptr = nt[ptr];
    for(int j = 0; j < p; j++) {
      ptr = nt[ptr];
    }
  }
  sort(cd, cd+nn);
  for(int i = 0; i < nn; i++) printf("%d\n", cd[i] + 1);
  return 0;
}

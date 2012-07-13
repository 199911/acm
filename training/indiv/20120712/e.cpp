#include <cstdio>
#include <cstring>
using namespace std;

int a[1<<17];

void init() {
  memset(a, -1, sizeof(a));
}

void update(int x) {
  for(int i = x; i < 1<<17; i += i&-i) 
    a[i]++;
}

int query(int x) {
  int ret = 0;
  for(int i = x; i > 0; i -= i&-i) {
    ret += a[i];
  }
  return ret;
}

#define N 66666

int x, y, n, l[N];

int main(){
  scanf( "%d", &n );
  memset(l, 0, sizeof(l));
  for(int i = 0; i < n; i++ ) {
    scanf( "%d%d", &x, &y );
    x++, y++;
    l[query(x)]++;
    update( x );
  }
  for(int i = 0; i < n; i++) printf("%d\n", l[i]);
  return 0;
}

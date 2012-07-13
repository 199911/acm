#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 11111

int A[N], u[N], v[N], n, m;
int p[N], ok, st, in[N];

void make() {
  for(int i = 0; i < n; i++) 
    p[i] = i;
}

int find(int x ) {
  return p[x] == x ? x : ( p[x] = find(p[x]));
}

void join(int x, int y) {
  p[find(x)] = find(y);
}

int main() {
  int cas = 1;
  while(true) {
    int a, b;
    n = m = 0;
    memset(in, 0, sizeof(in));
    while( scanf("%d%d", &a, &b), a > 0 ) {
      u[m] = a; v[m] = b;
      A[n++] = a;
      A[n++] = b;
      m++;
    }
    if( a == -1 ) break;
    sort(A, A+n);
    n = unique(A, A + n) - A;
    make();
    
    for(int i = 0; i < m; i++) {
      u[i] = lower_bound(A, A + n , u[i]) - A;
      v[i] = lower_bound(A, A + n , v[i]) - A;
      in[v[i]]++;
    }

    st = n; ok = m == n - 1;


    for(int i = 0, f = 0; i < n; i++) {
      if( in[i] > 1 ) ok = 0;
      else if ( in[i] == 0 ) {
        f++;
        if( f >= 2 ) {
          ok = 0;
        }
      }
    }

    for(int i = 0; i < m; i++) {
      if( find(v[i]) == find(u[i]) ) {
        ok = 0; break;
      } 
      join(u[i], v[i]);
    }

    if( n == 0 ) ok = 1;

    printf("Case %d is %sa tree.\n", cas++, ok ? "" : "not ");
  }
  return 0;
}


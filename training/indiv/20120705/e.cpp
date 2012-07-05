#include <cstdio>
#include <algorithm>
using namespace std;

#define LL long long

struct T {
  int l, r;
  LL s, a;
  T() {}
} t[444444];

void init(int p, int lf, int rt) {
  t[p].l = lf; t[p].r = rt; t[p].s = t[p].a = 0;
  int mid = (lf + rt) / 2;
  if( lf == rt ) return;
  init( p * 2, lf, mid);
  init( p * 2 + 1, mid + 1, rt);
}

void update(int p, int lf, int rt, LL a) {
  if( t[p].l >= lf && t[p].r <= rt ) {
    t[p].a += a;
    t[p].s += a * ( 1 + t[p].r - t[p].l );
    return;
  } else if ( t[p].l > rt || t[p].r < lf ) {
    return;
  }
  if( t[p].l == t[p].r ) return;
  update( 2 * p, lf, rt, a);
  update( 2 * p + 1, lf, rt, a);
  t[p].s = t[2 * p].s + t[2 * p + 1].s + ( t[p].r - t[p].l + 1 ) * t[p].a;
}

LL query(int p, int lf, int rt) {
  if( t[p].l >= lf && t[p].r <= rt ) {
    return t[p].s;
  } else if ( t[p].r < lf || t[p].l > rt ) {
    return 0;
  } else {
    int l = max(lf, t[p].l), r = min(rt, t[p].r);
    LL ret = query( p * 2, lf, rt) + query( p * 2 + 1, lf, rt) + (LL)( r - l + 1 ) * t[p].a;
//    printf("[%d %d] = %d\n", t[p].l, t[p].r, ret);
    return ret;
  }
}

int main(){
  int n, q;
  scanf( "%d%d", &n, &q );
  int x = 1;
  while( x < n ) x <<= 1;
  init(1, 1, x);

  for(int i = 0; i < n; i++) {
    scanf( "%d", &x );
    update(1, i + 1, i + 1, (LL)x);
  }

  while( q-- ) {
    char s[100];
    scanf("%s", s);
    if( s[0] == 'Q' ) {
      int a, b;
      scanf( "%d%d", &a, &b);
      printf("%lld\n", query(1, a, b));
    } else {
      int a, b; 
      LL c;
      scanf( "%d%d%lld", &a, &b, &c );
      update(1, a, b, c);
    }
    
  }
  return 0;
}

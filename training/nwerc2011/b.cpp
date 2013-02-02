#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define FOE(i,a,b) for(int i = a; i <= b; i++)
#define REP(i,n) FOR(i,0,n)
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))

LL a, b, n;

void find( int d, LL lm, LL ln, LL hm, LL hn ) {
  LL cm = lm + hm, cn = ln + hn;
  if ( a * cn == b * cm ) return;
  else if ( a * cn > b * cm ) {
    printf( "%s", d & 1 ? "L" : "R" );
    find( d + 1, cm, cn, hm, hn );
  } else {
    printf( "%s", d & 1 ? "R" : "L"  );
    find( d + 1, lm, ln, cm, cn );
  }
}

int main() {
  scanf( "%lld", &n );
  while( n-- ) {
    scanf( "%lld/%lld", &a, &b );
    find( 0, 0, 1, 1, 0 );
    puts( "" );
  }
  return 0;
}


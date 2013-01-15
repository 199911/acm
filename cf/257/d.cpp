#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define LL long long
#define N 111111

int n, a[N], sg[N], pg[N];

int solve( int A[], int k, int SG[], int PG[] ) {
  if ( k == 1 ) {
    SG[0] = 1;
    PG[0] = 1;
    return A[0];
  } else {
    int x = solve( A + 1, k - 1, SG + 1, PG + 1);
    if ( x >= A[0] ) { 
      SG[0] = -1;
      PG[0] = 1;
      return x - A[0];
    } else {
      SG[0] = 1;
      PG[0] = -1;
      return A[0] - x;
    }
  }
}

int main() {
  scanf( "%d", &n );
  for( int i = 0; i < n; i++ ) {
    scanf( "%d", &a[i] );
  }
  solve( a, n, sg, pg );
  int mul = pg[0];
  for( int i = 1; i < n; i++ ) {
    sg[i] *= mul;
    mul *= pg[i];
  }
  for( int i = 0; i < n; i++ ) {
    if ( sg[i] > 0 ) printf( "+" );
    else printf( "-" );
  }
  puts( "" );
  return 0;
}

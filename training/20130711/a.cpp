#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int mcs( int A[], int n ) {
  int tmp = 0, ret = 0;
  for( int i = 0; i < n; i++ ) {
    tmp += A[i];
    if ( tmp < 0 ) tmp = 0;
    ret = max( ret, tmp );
  }
  return ret;
}

int main() {
  int n, A[111];
  scanf( "%d", &n );
  int ans = 0;
  for( int i =0; i < n; i++ ) { 
    scanf( "%d", &A[i] );
    ans += A[i];
    A[i] = A[i] ? -1 : 1;
  }
  if ( ans == n ) printf( "%d\n", ans - 1 );
  else printf( "%d\n", ans + mcs( A, n ) );
  return 0;
}

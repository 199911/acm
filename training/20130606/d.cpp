#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, a[111111], T;

int main() {
  scanf( "%d", &T );
  while( T-- ) {
    scanf( "%d", &n );
    for( int i = 0; i < n; i++ ) scanf( "%d", &a[i] );
    int ans = 0;
    for( int ptr = 0; ptr < n; ptr++ ) {
      if( ans & 1 ) {
        while( ptr + 1 < n && a[ptr + 1] <= a[ptr] ) ptr++;
        ans++;
      } else {
        while( ptr + 1 < n && a[ptr + 1] >= a[ptr] ) ptr++;
        ans++;
      }
    }
    printf( "%d\n", ans );
  }
  return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int A[3][3];

int main(){
  for( int i = 0; i < 3; i++ ) 
    for( int j = 0; j < 3; j++ ) 
      scanf( "%d", &A[i][j] );
  int s = A[2][0] + A[0][2], d = A[2][0] + A[2][1] - A[0][1] - A[0][2];
  A[0][0] = ( s + d ) / 2;
  A[2][2] = s - A[0][0];
  int t = A[0][0] + A[0][1] + A[0][2];
  A[1][1] = t - s;

  for( int i = 0; i < 3; i++ ) 
    for( int j = 0; j < 3; j++ ) 
      printf( "%d%s", A[i][j], j == 2 ? "\n" : " " );
  return 0;
}

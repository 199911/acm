#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

// compute the last nonzero digit of m * ( m + 1 ) * ( m + 2 ) ... * n

int P( LL m, LL n ) {
  if ( m > n ) return 1;
  LL s = m / 5 + (m % 5 ? 1 : 0), t = n / 5;
  if ( t <= s + 1 ) {
    LL res = 1;
    for ( LL k = m; k <= n; k++ ) {
      LL x = k; 
//      printf( "x = %lld\n", x );
      while ( x % 10 == 0 ) { x /= 10; }
//      while ( res % 5 == 0 && x % 2 == 0 ) { res /= 5; x /= 2; }
//      while ( res % 2 == 0 && x % 5 == 0 ) { res /= 2; x /= 5; }
      res = res * ( x % 1000 );
//      printf("res = %lld\n", res);
    }
    while ( res % 10 == 0 ) res /= 10;
    return res % 10;
  }
  const int A[4] = {6, 2, 4, 8};
  const int D1[5] = {1, 4, 4, 2, 4};
  const int D2[5] = {1, 1, 2, 6, 4};
  LL ret = A[(t - s - 1) % 4] * P(s, t) * D1[m % 5] * D2[n % 5];
  while ( ret % 10 == 0 ) ret /= 10;
  return ret % 1000;
}


const int inv[] = {0, 1, 0, 7, 0, 0, 0, 3, 0, 9};
const int twos[] = {6, 2, 4, 8};
const int ms[] = {1, 1, 1, 3, 3, 3, 3, 1, 1, 9,
  9, 9, 9, 7, 7, 7, 7, 9, 9, 1};

int N, M;

int calc(int n){
  if(n <= 1){
    return 1;
  }

  return ms[n%20] * calc(n/2) * calc(n/5) * inv[calc(n/10)] % 10;
}

int fact2(int n){
  int ret = 0;
  for(;n;n/=2){
    ret += n / 2;
  }
  return ret;
}

int fact5(int n){
  int ret = 5;
  for(;n;n/=5){
    ret += n / 5;
  }
  return ret;
}

int solve(int a, int b){
  N = a; M = b;
  if(N == 0){
    return 1;
  }

  int two = fact2(N) - fact2(N - M);
  int five = fact5(N) - fact5(N - M);
  int m = calc(N) * inv[calc(N - M)] % 10;

  if(two == five){
    return m;
  }
  if(two > five){
    return m * twos[(two - five) % 4] % 10;
  }
  else {
    return 5;
  }
}

int mysolve(int a, int b) {
  if ( a && b ) return P( a - b + 1, a ) % 10;
  else return 1;
}

int main() {
  LL m, n;

  for ( int i = 0; i < 20000000; i++ ) {
    for ( int j = 0; j <= i; j++ ) {
      if ( j >= i - j ) {
        int a = solve(j, i - j), b =  mysolve(j, i - j) ;
        if ( a != b ) {
          printf( "%d %d ( his = %d | my = %d )\n", j, i - j, a, b );
        }
      }
    }
  }

  return 0;
}

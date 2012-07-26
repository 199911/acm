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

void genphi( LL ph[], int n ) {
  for ( int i = 0; i < n; i++ ) ph[i] = i;
  ph[1] = 0;
  for ( int i = 2; i < n; i++ ) { 
    if ( ph[i] == i ) {
      ph[i]--;
      for ( int j = i + i; j < n; j += i ) ph[j] = ph[j] / i * ( i - 1 );
    }
  }
}

LL gcd( LL a, LL b ) { return b ? gcd( b, a % b ) : a ; }
  
#define N 1500000
#define M 12158598919LL

LL ph[N], ps[N];
int n;

int find( int th, int k ) {
  for ( int i = 0; i <= k; i++ ) {
    if ( gcd( i, k ) == 1 && --th == 0 )
      return i;
  }
  return -1;
}

int main() {
  genphi( ph, N );
  ps[1] = 2;
  for ( int i = 2; i < N; i++ ) { 
    ps[i] = ps[i - 1] + ph[i];
    if ( ps[i] > M ) {
      n = i + 1;
      break;
    }
  }

  LL k;
  while ( scanf( "%lld", &k ), k ) {
    int de = lower_bound( ps, ps + n, k ) - ps;
    int no = find( k - ps[de - 1], de );
    printf( "%d/%d\n", no, de );
  }

  return 0;
}

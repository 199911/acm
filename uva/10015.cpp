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

#define N 44444

bool ip[N]; 
int pl[N], pn;

void seive( int n ) {
  pn = 0;
  memset( ip, 1, sizeof( ip ) );
  for ( int i = 2; i < n; i++ ) {
    if ( ip[i] ) {
      pl[pn++] = i;
      for ( int j = i + i; j < n; j += i ) ip[j] = 0;
    }
  }
}

int joseph( int n ) {
  int ans = 0;
  for ( int i = 1; i <= n; i++ ) {
    ans = ( ans + pl[n - i] ) % i;
  }
  return ans;
}

int main() {
  seive(N);
  int n ;
  while ( scanf( "%d", &n ), n ) {
    printf( "%d\n", joseph( n ) + 1 );
  }
  return 0;
}

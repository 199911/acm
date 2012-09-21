#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <bitset>
#include <map>
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

#define N 2222
#define MOD 1000000007

void mult( LL a[], LL b[], LL c[], int n ) {
  LL res[N], t1[N];
  REP( i , n ) {
    t1[i] = 0;
    FOE( j, 0, i ) {
      t1[i] += a[j] * b[i - j];
      t1[i] %= MOD;
    }
  }
  REP( i , n ) c[i] = t1[i];
}

void exp( LL a[], int n, LL k, LL r[] ) {
  LL res[N], t2[N];
  REP( i , n ) { res[i] = 0; t2[i] = a[i]; }
  res[0] = 1;
  while( k ) {
    if ( k & 1 ) mult( res, t2, res, n );
    mult( t2, t2, t2, n );
    k >>= 1;
  }
  REP( i, n ) r[i] = res[i];
}



int main() {
  LL a[N], b[N], c[N], k; 
  int n;
  cin >> n >> k;
  REP( i, n ) a[i] = 1;
  REP( i , n ) cin >> c[i];
  exp( a, n, k, b );
  mult( c, b, c, n );
  REP( i , n ) cout << c[i] << ( i == n - 1 ? "\n" : " " );
  return 0;
}

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

// generate all primes <= n
int l, r, ans;

void seive( int n ) {
  int B = sqrt( n + 1e-9 ), p[1<<15], pn = 0;
  bool ip[1<<18];

  CLR( ip, 1 );
  for( int i = 2; i <= B; i++ ) {
    if ( ip[i] ) {
      p[pn++] = i;
      if ( i >= l && i <= r && ( i % 4 == 1 || i == 2 ) ) ans++;

      for( int j = i + i; j <= B; j += i ) ip[j] = 0;
    }
  }

  for( int st = B + 1, en = B + B; st <= n; st += B, en += B ) {
    CLR( ip, 1 ); 
    for( int i = 0; i < pn; i++ ) {
      int pt = st / p[i] * p[i]; 
      if ( pt < st ) pt += p[i];
      while ( pt <= en ) ip[pt - st] = 0, pt += p[i];
    }
    for( int i = st; i <= en; i++ ) 
      if ( ip[i - st] ) { 
        if ( i >= l && i <= r && ( i % 4 == 1 || i == 2 ) ) ans++;
      }
  }
}

int main() {
  cin >> l >> r;
  ans = 0;
  seive( r );
  printf( "%d\n", ans );
  return 0;
}

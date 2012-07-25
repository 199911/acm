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

#define N (1<<17)

bool ip[N];
LL p[N], pn;

void seive( LL n ) {
  CLR(ip, 1);
  ip[0] = ip[1] = 0;
  pn = 0;
  for( LL i = 2; i < n; i++ ) {
    if ( ip[i] ) {
      p[pn++] = i;
      for ( int j = i + i; j < n; j += i ) 
        ip[j] = 0;
    }
  }
}

void factorize( LL x, LL p[], LL e[], LL r ) {
  LL res = x;
  r = 0;

  for ( int i = 0; res > 1 && i < pn && SQR(p[i]) <= x; i++ ) {
    if ( res % p[i] == 0 ) {
      p[r] = p[i];
      e[r]  =0;
      while ( res % p[i] == 0 ) {
        res /= p[i];
        e[r]++;
      }
      r++;
    }
  }

  if ( res > 1 ) {
    p[r] = res;
    e[r++] = 1;
  }
}

int main() {
  return 0;
}

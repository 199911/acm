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

const int MAXDIGIT = 100;

#define MPN 222

struct MP {
  int d[MPN], n, ofl;
  MP(): n(0), ofl(0) { memset(d, 0, sizeof(d)); }
  MP(int x): n(0), ofl(0) {
    memset(d, 0, sizeof(d));
    while( x ) {
      d[n++] = x % 10;
      x /= 10;
    }
  }
  void eat() {
    char str[MPN];
    scanf( "%s", str );
    n = strlen(str);
    for( int i = 0; i < n; i++ ) d[i] = str[n - i - 1] - '0';
  }

  int operator[] (int k) { return k < n ? d[k] : 0; }

  MP operator+( MP a ) {
    MP ret;
    int m = max(n, a.n);

    for( int i = 0; i < m; i++ ) 
      ret.d[i] = d[i] + a.d[i];

    for( int i = 0; i < m; i++ ) {
      ret.d[i+1] += ret.d[i] / 10;
      ret.d[i] %= 10;
    }

    if ( ret.d[m] ) m++;

    if ( m > MAXDIGIT ) ofl = 1;

    ret.n = m;

    return ret;
  }

  MP operator*( MP a ) {
    MP ret;
    if ( a.ofl || ofl || n + a.n - 1 > MAXDIGIT ) {
      ret.ofl = 1; return ret;
    }
    for ( int i = 0; i < n; i++ ) 
      for ( int j = 0; j < a.n; j++ ) 
        ret.d[i+j] += d[i] * a.d[j];
    for ( int i = 0; i < n + a.n; i++ ) {
      ret.d[i+1] += ret.d[i] / 10;
      ret.d[i] %= 10;
    }
    if ( ret.d[n + a.n - 1] ) ret.n = n + a.n;
    else ret.n = n + a.n - 1;

    if ( ret.n > MAXDIGIT ) ret.ofl = 1;
    return ret;
  }

  void out() { 
    for ( int i = n - 1; i >= 0; i-- ) printf("%d", d[i]); 
  }


};


#define N 5555


int main() {
  int n, m;

  bool ip[N];
  int pf[N];

  memset(ip, 1, sizeof(ip));

  for( int i = 0; i < N; i++ ) pf[i] = i;

  for ( int i = 2; i < N; i++ ) {
    if ( ip[i] ) {
      for ( int j = i + i; j < N; j += i ) {
        ip[j] = 0;
        if ( pf[j] == j ) pf[j] = i;
      }
    }
  }

  while( scanf( "%d%d", &n, &m ) != EOF ) {
    int ps[N], up[N], k = 0;

    memset(up, 0, sizeof(up));
    for( int i = 0; i < n; i++ ) {
      int a, b;
      scanf( "%d%d", &a, &b );
      if ( b == 0 ) continue;
//      printf( "a = %d | b = %d\n", a, b);
      up[a]++;
      up[a-b]--;
      up[b]--;
      k = max(k, a);
    }
    for( int i = 0; i < m; i++ ) {
      int a, b;
      scanf( "%d%d", &a, &b );
      if ( b == 0 ) continue; 
      up[a]--;
      up[a-b]++;
      up[b]++;
      k = max(k, a);
    }

    memset(ps, 0, sizeof(ps));
    ps[k] = up[k];


    for(int i = k - 1; i > 1; i--) {
      ps[i] = ps[i+1] + up[i];
    }

    int ok = 1;


    for( int i = k; i > 1; i-- ) {
      if ( !ip[i] ) {
        ps[pf[i]] += ps[i];
        ps[i/pf[i]] += ps[i];
        ps[i] = 0;
      } else {
        if ( ps[i] < 0 ) ok = 0;
      }
    }

    if ( !ok ) {
      puts("0");
    } else {
      MP res = MP(1);
      for( int i = 2; i <= k; i++ ) 
        if ( ip[i] && ps[i] ) 
          for ( int j = 0; j < ps[i]; j++ ) {
            res = res * MP(i);
          }
      if ( res.ofl ) {
        puts("-1");
      } else {
        res.out();
        puts( "" );
      }
    }

  }

  return 0;
}

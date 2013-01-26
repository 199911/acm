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

#define N 1111

LL a, m, p, q, r, s;

bool doit( LL mn, LL mx, LL ym, LL y, LL cnt[], LL &len) {
  int cn = 0;
  len = 0;
  if ( mn > mx || mx < 0 ) return false;
  for( int i = 0; ym > 0; i++ ) {
    cnt[i] = max( 0LL, min( mx / ym, (mn + ym - 1) / ym ) );
    mn -= ym * cnt[i];
    mx -= ym * cnt[i];
    len += cnt[i];
    ym /= y;
    if ( ym ) len++;
    cn = i + 1;
  }
  return true;
}

bool comp( LL a[], LL b[], int n ) {
  for( int i = 0; i < n; i++ )
    if ( a[i] != b[i] ) return a[i] < b[i];
  return false;
}

int main() {
  int cas = 1;
  while ( scanf( "%lld%lld%lld%lld%lld%lld", &a, &m, &p, &q, &r, &s ), a || m || p || q || r || s ) {
    printf( "Case %d: ", cas++ );
    if ( m == 1 ) {
      LL mn = r - p, mx = s - q;
      LL mna = ( mn +  a - 1 ) / a * a, mxa = mx / a * a;
      if ( mxa < 0 || mna > mxa ) {
        printf( "impossible\n" );
      } else {
        if ( mna <= 0 ) printf( "empty\n" );
        else printf( "%lld\n", mna / a );
      }
    } else {
      LL mc = 0, cnt[1111], len, ym = 1, ml = 1ll<<62, mcnt[1111], nn = 0;
      int ok = 0, n = 1;
      while( q - p <= s - r && q <= s ) {
        LL mn = r - p, mx = s - q;
        LL mna = ( mn +  a - 1 ) / a, mxa = mx / a;
        if ( doit( mna, mxa, ym, m, cnt, len ) ) {
          if ( len < ml || len == ml && comp( cnt, mcnt, n ) ) {
            copy( cnt, cnt + N, mcnt );
            nn = n;
            ml = len;
          }
          ok = 1;
        } 
        p *= m; q *= m;
        ym *= m; n++;
      }
      if ( !ok ) {
        puts( "impossible" );
      } else if( ml == 0 ) {
        puts( "empty" );
      } else {
        int op[N], po[N], k = 0;
        op[k] = 0;
        po[k] = 0;
        for( int i = 0; i < nn; i++ ) {
          if( mcnt[i] ) {
            if ( op[k] == 1 ) { 
              po[k] += mcnt[i];
              if ( i != nn - 1 ) {
                k++;
                op[k] = 2;
                po[k] = 1;
              }
            } else {
              k++;
              op[k] = 1;
              po[k] = mcnt[i];
              if( i != nn - 1 ) {
                k++;
                op[k] = 2;
                po[k] = 1;
              }
            }
          } else {
            if ( op[k] == 2 ) {
              if ( i != nn - 1 ) {
                po[k]++;
              } 
            } else {
              if ( i != nn - 1 ) {
                k++;
                op[k] = 2;
                po[k] = 1;
              }
            }
          }
        }
        for( int i = 1; i <= k; i++ ) {
          if ( i != 1 ) printf( " " );
          printf( "%d%s", po[i], op[i] == 1 ? "A" : "M" );
        }
        puts( "" );
      }
    }

  }
  return 0;
}

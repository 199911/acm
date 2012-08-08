#include <cstdio>
#include <cctype>
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

// partition tree

#define N (1<<18)

int A[N], srt[N], val[18][1<<18];
int L[N<<1], R[N<<1], n;
int sum[18][1<<18];

void build_tree( int p, int lay, int l, int r ) {
  L[p] = l; R[p] = r;

  if ( l == r ) return;

  int mi = ( l + r ) >> 1;
  LL vm = srt[mi];
  int lsame = mi - l + 1;
  for ( int i = l; i <= r; i++ ) {
    if ( val[lay][i] < vm ) lsame--;
  }

  for ( int i = l, lnt = 0, rnt = 0; i <= r; i++ ) {
    if ( val[lay][i] < vm || val[lay][i] == vm && lsame-- > 0 ) {
      val[lay + 1][l + lnt++] = val[lay][i]; 
    }
    else {
      val[lay + 1][mi + 1 + rnt++] = val[lay][i]; 
    }

    if ( lnt > mi - l + 1 ) while ( 1 );
    if ( rnt > r - mi ) while (1);

    sum[lay][i] = lnt;
  }

  build_tree( p * 2, lay + 1, l, mi);
  build_tree( p * 2 + 1, lay + 1, mi + 1, r );
}

void print() {
  int q[N], qt, qh, ly[N], cur = -1;
  qt = qh = 0;
  q[qt++] = 1;
  ly[1] = 0;

  while ( qt > qh ) {
    int w = q[qh++];
    if ( ly[w] > cur ) {
      cur = ly[w];
      puts( "" );
    } 
    printf( "[" );
    for ( int i = L[w]; i <= R[w]; i++ ) {
      printf("%lld(%d)%s", val[cur][i], sum[cur][i], i == R[w] ? "" : ",");
    }
    printf( "]" );


    if ( L[w] == R[w] || sum[cur][R[w]] == R[w] - L[w] + 1 ) {
    } else {
      q[qt++] = 2 * w;
      ly[2 * w] = cur + 1;
      q[qt++] = 2 * w + 1;
      ly[2 * w + 1] = cur + 1;
    }
  }
  puts( "" );
} 

void build() {
  REP( i, n ) srt[i] = A[i];
  sort( srt, srt + n );

  REP( i, n ) val[0][i] = A[i]; 
  build_tree( 1, 0, 0, n - 1 );
}

int query( int p, int ly, int l, int r, int k ) {
  if ( L[p] == R[p] ) return val[ly][l];

  int rnk = sum[ly][r] - ( l > L[p] ? sum[ly][l - 1] : 0 ), mid = ( L[p] + R[p] ) >> 1;

  if ( k <= rnk ) { // left subtree
    int lf = L[p] + ( l > L[p] ? sum[ly][l - 1] : 0 );
    int rt = L[p] + sum[ly][r] - 1;
    return query( p * 2, ly + 1, lf, rt, k);
  } else {  // right subtree
    int mid = ( R[p] + L[p] ) >> 1;
    int lf = mid + 1 + ( l == L[p] ? 0 : l - L[p] - sum[ly][l - 1] );
    int rt = mid + 1 + r - L[p] + 1 - sum[ly][r] - 1;

    return query( p * 2 + 1, ly + 1, lf, rt, k - rnk );
  }
}

int query( int l, int r, int k ) {
  return query( 1, 0, l, r, k );
}

int main() {
  return 0;
}

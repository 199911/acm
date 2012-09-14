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

#define N 100002

int A[N], m, n, k = 0, cnt[N], S[500][N], MP[N], PP[N];

int query( int l, int u ) {
//  printf( "[%d, %d]:\n", l, u);
  int ans = 0;
//  printf( "k = %d\n", k );
  REP( i, k ) {
    int s = l == 0 ? 0 : S[i][l - 1];
    int t = S[i][u];
    if ( t - s == PP[i] ) { 
      ans++; 
    }

  }
  return ans;
}

int main() {
  scanf( "%d%d", &n, &m );
  CLR( cnt, 0 );
  REP( i, n ) { 
    scanf( "%d", &A[i] );
    if ( A[i] <= n ) cnt[A[i]]++;
  }

  CLR( MP, -1 );
  k = 0;
  REP( i, n ) {
    if ( A[i] <= n && cnt[A[i]] >= A[i] && cnt[A[i]] <= n ) {
      if( MP[A[i]] == -1 ) { 
        PP[k] = A[i];
        MP[A[i]] = k++;
      }
    }
  }

  CLR( S, 0 ); 
  REP( i, n ) 
    REP( j, k ) 
      S[j][i] = (i == 0 ? 0 : S[j][i - 1] ) + ( A[i] == PP[j] );

  REP( i, m ) {
    int l, r;
    scanf( "%d%d", &l, &r );
    l--; r--;
    printf( "%d\n", query(l, r) );
  }

  return 0;
}

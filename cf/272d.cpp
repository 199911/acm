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

#define N 111111

PII A[N], B[N], C[N * 2];
LL M, ans;
LL f[N];
int n, m;

int main() {
  scanf( "%d", &n );
  ans = 1;
  REP( i, n ) {
    scanf( "%d%d", &A[i].first, &B[i].first );
    A[i].second = B[i].second = i;
    C[i * 2] = A[i];
    C[i * 2 + 1] = B[i];
  }
  scanf( "%lld", &M );
  f[0] = 1;
  FOR( i, 1, N ) f[i] = f[i - 1] * i;
  sort( C, C + 2 * n );

  m = unique( C, C + 2 * n ) - C;
  C[m++] = PII( 1 << 30, 1 << 30 );

  printf( "%lld\n", ans );

  return 0;
}

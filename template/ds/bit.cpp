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

#define N 111111

void update( int b[], int k, int a ) {
  for( int i = k; i < N; i += i & - i ) 
    b[i] += a;
}

LL query( int b[], int k ) {
  LL ans = 0;
  if ( k == 0 ) return 0;
  for( int i = k; i > 0; i -= i & -i )
    ans += b[i];
  return ans;
}

int discretize( int A[], int n ) {
  int S[N];
  REP( i, n ) S[i] = A[i];
  sort( S, S + n );
  int m = unique( S, S + n ) - S;
  REP( i, n ) A[i] = lower_bound( S, S + m, A[i] ) - S;

  return m;
}

int main() {
  return 0;
}

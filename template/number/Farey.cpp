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

int C[222], D[222];

int rank(int mi, int n ) {
  int cnt = 0;
  for (int q = 1; q <= n; ++q)
    cnt += (q * mi / n) * (q * q <= n ? C[q] : D[n / q]);
  return cnt;
}

int precompute(int n) {
  for (int r = 1; r * r <= n; ++r) D[r] = 1;
  for (int r = 1; r * r <= n; ++r)
    for (int t = 2; t <= r; ++t) D[r] -= D[r / t];

  int m; for (m = 1; m * m <= n; ++m) C[m] = 1;
  for (int q = m - 1; q >= 1; --q)
    for (int t = q + q; t <= n; t += q)
      if (t * t <= n) C[q] -= C[t]; else C[q] -= D[n / t];
}


void farey( int n, int k, int &nom, int &det ) {
  precompute(n);
  int lo = 0, hi = 2 * n, mi;
  while (lo + 1 < hi) {
    mi = (lo + hi) >> 1;
    if (rank( mi, n ) <= k) lo = mi; else hi = mi;
  }
  int mp1 = hi, mp2 = hi, mq1 = n, mq2 = n;
  for (int q = 1; q <= n; ++q) {
    int p = (lo * q + n - 1) / n;
    int d = __gcd(p, q); int tp = p / d, tq = q / d;
    if (mq1 * tp < mp1 * tq) {
      mp2 = mp1; mq2 = mq1;
      mp1 = tp; mq1 = tq;
    } else if (mp1 * tq < mq1 * tp && mq2 * tp < mp2 * tq) {
      mp2 = tp; mq2 = tq;
    }
  }
  int kk = k - rank(lo, n);
  for (int i = 1; i <= kk; ++i) {
    mp1 = (mq1 + n) / mq2 * mp2 - mp1;
    mq1 = (mq1 + n) / mq2 * mq2 - mq1;
    swap(mp1, mp2); swap(mq1, mq2);
  }
  nom = mp1;
  det = mq1;
}


int main() {
  int n, k, a, b;
  while( scanf( "%d%d", &n, &k ) != EOF ) {
    farey( n, k, a, b );
    printf( "%d/%d\n", a, b );
  }
  return 0;
}

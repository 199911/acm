#include <cstdio>
#include <algorithm>
using namespace std;

#define maxsqrtn 33

int n, k;
int C[222], D[222];

int rank(int mi) {
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


int main() {
    scanf("%d%d", &n, &k);
  precompute(n);
    int lo = 0, hi = 2 * n, mi;
  while (lo + 1 < hi) {
    mi = (lo + hi) >> 1;
    if (rank(mi) <= k) lo = mi; else hi = mi;
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
  int kk = k - rank(lo);
    for (int i = 1; i <= kk; ++i) {
      mp1 = (mq1 + n) / mq2 * mp2 - mp1;
      mq1 = (mq1 + n) / mq2 * mq2 - mq1;
      swap(mp1, mp2); swap(mq1, mq2);
    }
  printf("%d/%d\n", mp1, mq1);
  return 0;
}

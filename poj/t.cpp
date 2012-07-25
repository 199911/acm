#include <cstdio>

// returns the gcd of a and b.
inline long long gcd(long long a, long long b) {
  if (a)
    while (a ^= b ^= a ^= b %= a);
  return b;
}

// returns the smaller value between a and b.
inline long long min(long long a, long long b) {
  return a < b ? a : b;
}

// returns a*b%m. the function works for m < 2^55
inline long long mul(long long a, long long b, long long m) {
  a %= m;
  b %= m;
  long long t = 0;
  while (b) {
    t += a*(b&255);
    t %= m;
    a <<= 8;
    b >>= 8;
    a %= m;
  }
  return t;
}

// returns n^p%m.
inline long long pow(long long n, long long p, long long m) {
  long long t = 1;
  while (p) {
    if (p&1)
      t = mul(t, n, m);
    n = mul(n, n, m);
    p >>= 1;
  }
  return t;
}

// returns (s^2 + 1)%p. it is used as a pseudo-random generator.
inline long long rand(long long s, long long p) {
  long long t = mul(s, s, p) + 1;
  if (t == p)
    return 0;
  else
    return t;
}

//returns (s^2 + a)%p. it is used as a stronger pseudo-random generator.
inline long long rand(long long s, long long a, long long p) {
  long long t = mul(s, s, p) + a;
  if (t >= p)
    return t - p;
  else
    return t;
}

// returns true if a is a witness of p.
inline bool witness(long long p, long long a) {

  // decompose p - 1 into t*2^c where t is odd.
  int c = 0;
  long long t = p - 1;
  while (!(t&1)) {
    ++c;
    t >>= 1;
  }

  // a is not a witness if a^t, when repeated squaring, meet -1 before 1.
  a = pow(a, t, p);
  if (a == 1 || a + 1 == p)
    return 0;
  while (--c) {
    a = mul(a, a, p);
    if (a + 1 == p)
      return 0;
  }

  /* for prime p, a^(p - 1) must be 1. therefore if a^t != 1, a^(t*2^s)
   * must be -1 for some 0 <= s < c and the function
   * should have returned 0 in the while loop.
   */
  return 1;
}

// returns true if p is a prime(pseudo-prime).
// Miller-Rabin primality test is used.
bool isprime(long long p) {

  // handle trivial case: p is even.
  if (p == 2)
    return 1;
  if (!(p&1) || p < 2)
    return 0;

  // try 16 random numbers. if any one of them is a witness, p is not a prime.
  long long s = 1;
  for (int r = 0; r < 16; ++r) {
    s = rand(s, p);
    if (!s)
      s = r%(p - 1) + 1;
    if (witness(p, s))
      return 0;
  }

  // we treat p as a prime if all 16 rounds are passed.
  return 1;
}

/* returns a factor of p other than 1. t changes the random function.
 * Pollard's rho algorithm is used.
 */
long long r(long long p, long long t) {
  long long x = 2, y = 2, d;
  do {
    x = rand(x, t, p);
    y = rand(rand(y, t, p), t, p);
    d = gcd(x - y, p);
    if (d < 0)
      d = -d;
  } while (d == 1);
  return d;
}

// returns the smallest prime factor of p.
long long s(long long p) {

  /* Miller-Rabin primality test is usually faster than Pollard's rho algorithm.
   * thus we run the test first.
   */
  if (isprime(p))
    return p;

  if (!(p&1))
    return 2;

  /* we confirm any number passed the test is not a prime.
   * thus we try different random functions and apply
   * Pollard's rho algorithm until we find a non-trivial factor.
   */
  long long t = r(p, 1);
  for (int c = 2; t == p; ++c)
    t = r(p, c);

  // the smallest prime factor of p is that of t or that of p/t.
  if (t*t == p)
    return s(t);
  return min(s(t), s(p/t));
}

long long n, d;
int T;

int main() {
  scanf("%d", &T);
  ++T;
  while (--T) {
    scanf("%lld", &n);
    if (!(n&1))
      d = 2;
    else
      d = s(n);
    if (d == n)
      puts("Prime");
    else
      printf("%lld\n", d);
  }
  return 0;
}

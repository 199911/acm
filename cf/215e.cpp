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

LL mu[111];
bool ip[111];

void gen_mu( int n ) {
  REP( i, n ) { 
    mu[i] = 1;
    ip[i] = 1;
  }
  mu[1] = 1;
  ip[1] = 0;
  for( int i = 2; i < n; i++ ) {
    if ( ip[i] ) {
      mu[i] = -1;
      for( int j = i + i; j < n; j += i ) {
        ip[j] = 0;
        if ( j % i * i ) mu[j] = 0;
        else mu[j] = mu[j / i] * (-1);
      }
    }
  }
}

LL doit( LL x ) {
  int len = 0;
  for( LL i = 1; i <= x; i <<= 1 ) len++;

  LL ans = 0;
  for( int l = 1; l <= len; l++ ) {
    LL cnt[111];
    CLR( cnt, 0 );
    for( int k = 1; k < l; k++ ) {
      if ( l % k == 0 ) {
        if ( l == len ) {
          LL mp = 0, mq = 1LL << k - 1;
          for( int i = 0; i < l / k; i++ ) {
            mp <<= k; mp |= 1LL;
          }
          if ( mp * mq <= x ) {
            for( int i = k - 1; i >= 0; i-- ) {
              if ( (mq | (1LL << i)) * mp <= x ) mq |= 1LL << i;
            }
            cnt[k] += mq - (1LL << k - 1) + 1;
          } else {
          }
        } else {
          cnt[k] += 1LL << k - 1;
        }
        for( int j = k + k; j < l; j += k ) cnt[j] -= cnt[k];
        ans += cnt[k];
      }
    }
  }
  return ans;
}

int main() {
  LL l, u;
  cin >> l >> u;
  cout << doit( u ) - doit( l - 1 ) << endl;
  return 0;
}

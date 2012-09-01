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

#define N 18003001

int c[6001];

int pr( int x ) {
  if ( x <= 1 ) return 0;
  for( int i = 2; i * i <= x; i++ ) if ( x % i == 0 ) return 0;
  return 1;
}

int main() {
  int n, s;
  cin >> n;
  s = (n + 1) * n / 2;

  fill( c + 1, c + n + 1, 1 );
  if ( pr( s ) ) {
  } else if ( s % 2 == 0 ) {
    for( int i = 1; i <= n; i++ ) {
      if ( pr( i ) && pr( s - i ) ) {
        c[i] = 2;
        break;
      }
    }
  } else {
    if ( pr( s - 2 ) ) {
      c[2] = 2;
    } else {
      s -= 3;
      c[2] = c[1] = 3;
      for( int i = 3; i <= n; i++ ) {
        if ( pr( i ) && pr( s - i ) ) {
          c[i] = 2;
          break;
        }
      }
    }
  }

  if ( s == 0 ) puts( "-1" ); 
  else
    for( int i = 1; i <= n; i++ ) {
      printf("%d%s", c[i], i == n ? "\n" : " ");
    }
  return 0;
}

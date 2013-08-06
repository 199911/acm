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

char s[N], S[N];
int p[N], n, t, x, y ;

int main () {
  scanf( "%s" ,s ) ;
  n = strlen ( s ) ;
  for ( int i =0; i < n ; i ++) {
    S [2* i ]= '# '; S [2* i +1]= s [ i ]; }
  S [2* n ]= '# '; n = n *2+1;
  for ( int i =0; i < n ; i ++) {
    if ( p [ t ]+ t >= i ) p [ i ]= min ( p [2* t - i ] , p [ t ]+ t - i ) ;
    x =i - p [ i ]; y = i + p [ i ];
    while (x >0&& y <n -1&& S [x -1]== S [ y +1]) x - - , y ++ , p [ i
      ]++;
    if (! i || i+ p [ i ] > t + p [ t ]) t = i ;
  }
  for ( int i =0; i < n ; i ++) printf ( "%d\n " ,p [ i ]) ;
  return 0;
}


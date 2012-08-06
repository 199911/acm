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

// given date, find which day is it
// monday = 0, tuesday = 1, ....

int weekday( int y, int m, int d ) {
  if ( m <= 2 ) { 
    m += 12;
    y--; 
  } 

  int w = 0;
  if ( y < 1752 || ( y == 1752 &&  m < 9 ) || ( y == 1752 && m == 9 && d < 3 ) ) {
    w = ( d + 2 * m + 3 * ( m + 1 ) / 5 + y + y / 4 + 5) % 7;
  } else {
    w = ( d + 2 * m + 3 * ( m + 1 ) / 5 + y + y / 4 + y / 100 + y / 400 ) % 7;
  }
}

int main() {
  return 0;
}

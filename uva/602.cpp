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

string mth[] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
string wdy[] = { "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur", "Sun" };

int dmth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int leap( int x ) {
  if ( x <= 1752 ) return x % 4 == 0;
  else return x % 400 == 0 || x % 4 == 0 && x % 100;
}

bool valid ( int y, int m, int d ) {
  if ( y < 0 ) return false;
  if ( m > 12 ) return false;
  if ( y == 1752 && m == 9 && d > 2 && d < 14 ) return false;
  if ( m == 2 ) {
    return d <= dmth[m] + !!leap( y );
  } else {
    return d <= dmth[m];
  }
}

int weekday( int y, int m, int d ) {
  if ( m <= 2 ) { 
    m += 12;
    y--; 
  } 

  int w = 0;
  if ( y < 1752 || ( y == 1752 &&  m < 9 ) || ( y == 1752 && m == 9 && d < 3 ) ) {
    w = ( d + 2 * m + 3 * ( m + 1 ) / 5 + y + y / 4 + 5) % 7;
  } else {
    w = ( d + 2 * m + 3 * ( m + 1 ) / 5 + y + y / 4 - y / 100 + y / 400 ) % 7;
  }

  return w;
}

int main() {
  int y, m, d;

  while ( cin >> m >> d >> y && m || d || y ) {
    if ( ! valid( y, m, d ) ) {
      printf( "%d/%d/%d is an invalid date.\n", m, d, y );
    } else {
      printf("%s %d, %d is a %sday\n", mth[m].c_str(), d, y, wdy[weekday( y, m, d)].c_str() );
    }
  }
  return 0;
}

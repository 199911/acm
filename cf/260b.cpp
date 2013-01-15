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

int dy[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool check( string str ) {
  int m, d, y;
  sscanf( str.c_str(), "%d-%d-%d", &d, &m, &y );
  if ( y < 2013 || y > 2015 || m <= 0 || m >= 13 || d <= 0 || d > dy[m] ) return false;
  return true;
}

int main() {
  string is, ls;
  int n, feq;
  cin >> is;
  map<string,int> mp;

  n = is.length();
  feq = 0;

  for( int i = 0; i < n - 9; i++ ) {
    string str = is.substr( i, 10 );
    int ok = 1;
    for( int j = 0; j < 10; j++ ) {
      if ( str[j] == '-' ) ok &= j == 2 || j == 5;
      if ( j == 2 || j == 5 ) ok &= str[j] == '-';
    }
    if ( ok && check( str ) ) {
      map<string, int>::iterator it = mp.find( str );
      if ( it == mp.end() ) {
        mp.insert( make_pair( str, 1 ) );
        if ( feq == 0 ) {
          feq = 1;
          ls = str;
        }
      } else {
        int tmp = mp[str];
        tmp++;
        mp[str] = tmp;
        if ( tmp > feq )  {
          feq = tmp;
          ls = str;
        }
      }
    }
  }

  cout << ls << endl;

  return 0;
}

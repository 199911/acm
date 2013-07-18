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

int cnt[33], A[33], B[33];

int main() {
  string str;
  cin >> str;
  CLR( cnt, 0 );
  REP( i, str.length() ) cnt[str[i] - 'A']++;
  REP( i, 26 ) A[i] = cnt[i];

  cin >> str;
  CLR( cnt, 0 );
  REP( i, str.length() ) cnt[str[i] - 'A']++;
  REP( i, 26 ) B[i] = cnt[i];

  sort( A, A + 26 );
  sort( B, B + 26 );

  int ok = 1;
  REP( i, 26 ) if ( A[i] != B[i] ) ok = 0;

  cout << ( ok ? "YES" : "NO" ) << endl;
  return 0;
}

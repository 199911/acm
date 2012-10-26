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

#define N 555555

int Q[20][N], LOG[N];

void build( int A[], int n ) {
	LOG[1] = 0;
	FOE( i, 1, n ) LOG[i] = LOG[i / 2] + 1;
	REP( i, n ) Q[0][i] = A[i];
	
	FOE( j, 1, LOG[n] ) {
		REP( i, n ) {
			int b = min( n - 1, i + (1 << j) );
			Q[j][i] = max( Q[j - 1][i], Q[j - 1][b] );
		}
	}
}

int query( int l, int r ) {
	int len = r - l + 1, ln = 1 << LOG[len];
	return max( Q[LOG[len]][l], Q[LOG[len]][r - ln + 1] );
}

int main() {
  return 0;
}

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

int main() {
	string line;

	int n, m, k;
	int x[5555], y[5555], z[5555];
	
	cin >> m;
	REP(i, m ) cin >> x[i];
	cin >> n;
	REP( i, n ) cin >> y[i];
	cin >> k;
	REP( i, k ) cin >> z[i];
	sort( x, x + m );
	sort( y, y + n );
	sort( z, z + k );

	double r1 = x[m - 1], p1 = y[n - 1], p2 = z[0];
	double a, b;

	cin >> a >> b;

	double r = r1 * sqrt( b * p1 / ( a * p2 + b * p1 ) );

	printf( "%.7f\n", r );

	return 0;
}

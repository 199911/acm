#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
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

void genphi( int ph[], int n ) {
	for ( int i = 0; i < n; i++ ) ph[i] = i;
	ph[1] = 0;
	for ( int i = 2; i < n; i++ ) 
		if ( ph[i] == i ) {
			ph[i]--;
			for ( int j = i + i; j < n; j += i ) ph[j] = ph[j] / i * ( i - 1 );
		}
}

#define N 2000005
int ph[N], d[N];
LL ps[N];

int main() {
	genphi( ph, N );
	d[2] = 1;
	d[1] = 0;
	ps[2] = 1;
	ps[1] = 0;

	for ( int i = 3; i < N; i++ ) { 
		d[i] = d[ph[i]] + 1;
		ps[i] = d[i] + ps[i - 1];
	}

	int T;
	scanf( "%d", &T );
	while ( T-- ) {
		int a, b;
		scanf( "%d%d", &a, &b );
		printf( "%lld\n", ps[b] - ps[a - 1]);
	}
  return 0;
}

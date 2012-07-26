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

void genphi( int phi[], int n ) {
	for ( int i = 0; i < n; i++ ) 
		phi[i] = i;
	phi[1] = 0;
	for ( int i = 2; i < n; i++ ) {
		if ( phi[i] == i ) {
			phi[i]--;
			for ( int j = i + i; j < n; j += i ) 
				phi[j] = phi[j] / i * ( i - 1 );
		}
	}
}

#define N 50005

int ph[N], ps[N];

int main() {
	
	genphi(ph, N);

	ph[1] = ph[0] = 0;
	ps[2] = ph[2];

	for ( int i = 3; i < N; i++ ) {
		ps[i] = ph[i] + ps[i-1]; 
	}

	int n;
	while ( scanf( "%d", &n ), n ) {
		printf( "%d\n", 2 * ps[n] + 1 );
	}


  return 0;
}

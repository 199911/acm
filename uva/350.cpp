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


int z, a, m;

inline int f( int x ) {
	return ( x * z + a ) % m;
}

int detect( int seed, int &s, int &p ) {
	int i = f(seed), j = f(f(seed)); 
	s = 0, p = 1;


	while ( i != j ) { 
		i = f(i), j = f(f(j));
	}

	j = i; i = seed;

	while ( i != j ) { 
		i = f(i); 
		j = f(j);
		s++;
	}

	j = f(i);

	while ( i != j ) j = f( j ), p++;

	return s;
}

int main() {
	int seed, cas = 1;
	while ( cin >> z >> a >> m >> seed, z || a || m || seed ) {
		int s, p;
		detect(seed, s, p);
		printf( "Case %d: %d\n", cas++, p);
	}
  return 0;
}

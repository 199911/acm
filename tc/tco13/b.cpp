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

int l[55], r[55], d, n, mn, md, ml;

#define LT(a,b,c,d) ((LL)(a)*(d)<(LL)(b)*(c))

bool test( int nu, int de ) {
	for( int i = 1; nu * i <= de * d; i++ ) 
		for( int j = 0; j < n; j++ ) 
			if ( LT(l[j],1,nu*i,de) && LT(nu*i,de,r[j],1) ) return false;
	return true;
}

struct TheFrog {
	double getMinimum( int D, vector<int> L, vector<int> R ) {
		n = L.size();
		for( int i = 0; i < n; i++ ) {
			l[i] = L[i];
			r[i] = R[i];
		}
		md = 1;
		mn = 1<<29;

		for( int i = 0; i < n; i++ ) {
			for( int j = 1; j <= r[i]; j++ ) {
				if ( test( r[i], j ) && LT( r[i], j, mn, md ) ) {
					mn = r[i];
					md = j;
				}
			}
		}

		return (double)(mn)/md;
	}
};

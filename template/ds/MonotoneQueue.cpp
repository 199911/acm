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

#define N 1111111

struct MQ {
	pair<int,int> q[N];
	int qh, qt, h, t;
	void init() { qh=qt=h=t=0; }
	void enq(int x){
		while( qt > qh && q[qt - 1].second < x ) qt--;
		q[qt++] = pair<int,int>(t++, x);
	}
	void deq() { if( h++ == q[qh].first ) qh++; }
	int max() { return qt == qh ? -1 : q[qh].second; }
} Q;

int main() {
	int T;
	scanf( "%d", &T );
	while( T-- ) {
		char str[11];
		Q.init();
		while( 1 ) {
			scanf( "%s", str );
			if ( str[0] == 'E' ) {
				break;
			} else if ( str[0] == 'S' ) {
				continue;
			} else if ( str[0] == 'Q' ) {
				printf( "%d\n", Q.max() );
			} else if ( str[0] == 'C' ) {
				int x;
				scanf( "%*s%d", &x );
				Q.enq( x );
			} else if ( str[0] == 'G' ) {
				Q.deq();
			}
		}
	}
	return 0;
}

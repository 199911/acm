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

int s[111], n;

LL test( int pt ) {
	LL ans = 0;
	for( int i = 0; i < n; i++ ) 
		ans += s[i] /  pt;
	return ans;
}

struct TheOlympiadInInformatics { 
  int find(vector <int> sums, int k) { 
  	int mx = -1, mn = 0;
  	LL sm = 0;
  	n = sums.size();
  	for( int i = 0; i < n; i++ ) {
  		s[i] = sums[i];
  		mx = max( mx, s[i] );
  		sm += s[i];
		}
		
		if ( k == 0 ) return mx;
		if ( k > sm ) return 0;

		mx++;
		mn = 0;

		while( mx > mn + 1 ) {
			int mid = ( mx + mn ) / 2;
			LL cnt = test( mid );
			if ( cnt > k ) {
				mn = mid;
			} else {
				mx = mid;
			}
		}
		return mn;
  } 
  
 
}; 



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor

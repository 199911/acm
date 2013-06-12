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

int rem[111], n;

string remove( string a, int k ) {
	int l = a.length() / 2;
	string ret;
	for( int i = 0; i < l; i++ ) if ( i != k ) ret.append( 1, a[i] );
	for( int i = 0; i < l; i++ ) if ( i != k ) ret.append( 1, a[i + l] );
	return ret;
}

bool comp( string s, string t ) {
	int k = min( s.length(), t.length() );
	for( int i = 0; i < k; i++ ) 
		if ( s[i] != t[i] ) return s[i] > t[i];
	return false;
}

struct TheLargestString { 
  string find(string s, string t) { 
  	n = s.length();
		CLR( rem, 0 );
		for( int st = 0; st < n; st++ ) {
			int mk = -1;
			for( int i = st; i < n; i++ ) 
				if ( mk == -1 || s[mk] < s[i] ) mk = i;
			rem[mk] = 1;
			st = mk; 
		}
		string ret;
		for( int i = 0; i < n; i++ ) if ( rem[i] ) ret.append( 1, s[i]  );
		for( int i = 0; i < n; i++ ) if ( rem[i] ) ret.append( 1, t[i] );

		int k = ret.length() / 2, del = 0;

		for( int i = 0; i < k; i++ ) {
			string tmp = remove( ret, i - del );
			if ( comp( tmp, ret ) ) {
				del++;
				ret = tmp;
			} 
		}

		return ret;
  } 
  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ab"; string Arg1 = "zy"; string Arg2 = "by"; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "abacaba"; string Arg1 = "zzzaaaa"; string Arg2 = "cbaaaa"; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "x"; string Arg1 = "x"; string Arg2 = "xx"; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "abbabbabbababaaaabbababab"; string Arg1 = "bababbaabbbababbbbababaab"; string Arg2 = "bbbbbbbbbbbbbbbbbbaaab"; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 

int main() {
  TheLargestString ___test; 
  ___test.run_test(-1); 
} 
// END CUT HERE

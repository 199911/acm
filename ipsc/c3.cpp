#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

#define LL long long

map<LL, LL> memo;

int B[] = { 1894607624, 1927505134, 1861486949, 2052221263, 1953703270, 1772249212, 1704106159, 1607055075, 1829198849 };
std::vector<int> A(B,B+9);

long long t(long long n) {
	if ( memo.find(n) != memo.end() ) return memo[n];
	long long z=n;
	//for (long long a=2; a<n; ++a) if (t(a)>=a) if (n%a==0) { z/=t(a); z*=t(a)-1; }
	for( long long x = 2; x * x <= n; x++ ) {
		if ( n % x ) continue;
		LL a = x;
		if ( t(a) >= a ) {  z /= t(a); z *= t(a) - 1; } 
		if ( x * x != n ) { 
			a = n / x;
			if ( t(a) >= a ) {  z /= t(a); z *= t(a) - 1; } 
		}
	}
	LL ans = std::min(z+1,n);
	memo[n] = ans;
	return ans;
}

/*
	 int main() {
	 memo.clear();
	 sort( A.begin(), A.end() );
	 for (int i=0; i<4; ++i) A[i+5] ^= t(A[i+1]-A[0])>>7;
	 long long z = std::max( t(A[0])-1, A[0]+1-t(A[0]) );
	 int sz = A.size();
	 for (long long i=0; i<z % sz; ++i) std::rotate( A.begin(), A.begin()+1, A.end() );
	 A.insert( A.begin()+1, z );
	 for (long long x=8; x<1e7; ++x) {
	 int y = A[x/4]>>(18-6*(x%4))&63;
	 if (!y) break;
	 if (y<60) std::cout << char(31+y); else std::cout << A[y-60];
	 }
	 }
 */

int main() {
	while( 1 ) {
		memo.clear();
		A = vector<int>(B, B+9);
		sort( A.begin(), A.end() );
		for (int i=0; i<4; ++i) A[i+5] ^= t(A[i+1]-A[0])>>7;
		long long z = std::max( t(A[0])-1, A[0]+1-t(A[0]) );
		int sz = A.size();
		for (long long i=0; i<z % sz; ++i) std::rotate( A.begin(), A.begin()+1, A.end() );
		A.insert( A.begin()+1, z );
		stringstream ss;
		for (long long x=8; x<1e7; ++x) {
			int y = A[x/4]>>(18-6*(x%4))&63;
			if (!y) break;
			if (y<60) ss << char(31+y); else ss << A[y-60];
		}

		string tmp;
		cout << ss.str() << endl;
		ss >> tmp;
		if ( tmp.compare( "CHANGE" ) == 0 ) {
			LL a, b;
			ss >> a;
			ss >> tmp;
			ss >> b;
			printf( "%lld -> %lld\n", a, b );
			for( int i = 0; i < 9; i++ ) if ( B[i] == a ) B[i] = b;
		} else {
			cout << tmp << endl;
			break;
		}
	}
}


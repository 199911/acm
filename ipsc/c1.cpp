#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define LL long long

int B[] = { 1894607624, 1927505134, 1861486949, 2052221263, 1953703270, 1772249212, 1704106159, 1607055075, 1829198849 };
std::vector<int> A(B,B+9);

map<LL,LL> memo;


long long t(long long n) {
	long long z=n;
	if ( memo.find( n ) != memo.end() ) return memo[n];
	//for (long long a=2; a<n; ++a) if (t(a)>=a) if (n%a==0) { z/=t(a); z*=t(a)-1; }
	for( long long a = 2; a * a <= n; a++ ) {
		if ( n % a == 0 ) {
			if ( t(a) >= a ) { z /= t(a); z *= t(a) - 1; }
			if( a * a != n ) {
				if( t( n / a) >= a ) {
					z /= t( n / a );
					z *= t( n / a ) - 1;
				}
			}
		}
	}

	LL ans = std::min(z+1,n);
	memo[n] = ans;
	return ans;
}

int main() {
	memo.clear();
	sort( A.begin(), A.end() );
	for (int i=0; i<4; ++i) A[i+5] ^= t(A[i+1]-A[0])>>7;
	long long z = std::max( t(A[0])-1, A[0]+1-t(A[0]) );
	int size = A.size();
	int mid = z % size;
	//for (long long i=0; i<z; ++i) std::rotate( A.begin(), A.begin()+1, A.end() );
	rotate( A.begin(), A.begin() + mid, A.end() );
	A.insert( A.begin()+1, z );
	for (long long x=8; x<1e7; ++x) {
		LL y = A[x/4]>>(18ll-6ll*(x%4ll))&63ll;
		printf( "y = %lld\n", y);
		if (!y) break;
		if (y<60) std::cout << (char)(31+y); 
		//else std::cout << "troll(" << A[y-60] << ")";
	}
	return 0;
}

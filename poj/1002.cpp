#include <cstdio>
#include <map>
using namespace std;

int cd[] = { 2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9 }, tc;
char str[111];
map<int,int> mp;

int main() {
	scanf( "%d", &tc );
	while( tc-- ) {
		scanf( "%s", str );
		int ret = 0;
		for( int i = 0; str[i]; i++ ) {
			if ( str[i] >= '0' && str[i] <= '9' ) { 
				ret *= 10;
				ret += str[i] - '0';
			} else if ( str[i] >= 'A' && str[i] <= 'Z' ) {
				ret *= 10;
				ret += cd[str[i] - 'A'];
			}
		}
		mp[ret]++;
	}
	int last = -1, ok = 0;
	for( map<int,int>::iterator it = mp.begin(); it !=  mp.end(); it++ ) {
		if ( it->second > 1 ) {
			printf( "%03d-%04d %d\n", it->first / 10000, it->first % 10000, it->second );
			ok = 1;
		}
	}
	if ( !ok ) puts( "No duplicates." );
	return 0;
}

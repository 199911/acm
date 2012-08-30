#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

int main() {
	char str[1111], out[1111];
	scanf( "%s", str );

	int n = strlen(str);
	int fl = 0;
	for( int ptr = 0; ptr < n; ) {
		while( ptr < n && str[ptr] == 'W' && str[ptr + 1] == 'U' && str[ptr + 2] == 'B') {
			ptr += 3;
		}
		memset(out, 0, sizeof(out));
		for(int k = ptr; ptr < n && (str[ptr] != 'W' || str[ptr + 1] != 'U' || str[ptr +  2] != 'B'); ptr++) {
			out[ptr - k] = str[ptr];
		}
		if ( fl ) {
			printf(" ");
		}
		fl = 1;
		printf("%s", out);
	}
	puts("");
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

int ret, n, a[1005],test;

int main() {
	scanf("%d", &test);
	while (test--){
		scanf("%d", &n);
		ret = 0;
		FOR(i, 0, n){
			scanf("%d", &a[i]);
			FOR(j, 0, i)
				if (a[j] <= a[i]) ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}

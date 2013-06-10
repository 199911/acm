#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

int main() {
	printf("%d\n",1);
	int n = 3000;
	printf("%d\n",n);
	for (int i=0; i<n; i+=2) {
		printf("%d %d\n",i/2+5,i/2*3+2);
		printf("%d %d\n",i/2+5,i/2*3+3);
	}
	int m = 3000;
	printf("%d\n",m);
	for (int i=0; i<m-1; i++)
		printf("%d %d %d\n",i+1,i+2,2);
	printf("%d %d %d\n",1,n,(n-1)*2);
	
	return 0;
}

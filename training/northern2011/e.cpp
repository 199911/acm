#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int n;
char s[1005][45];
int done = 0;
set<string> v;

int main() {
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		scanf("%s",s[i]);	
	}
	for (int i=1; i<=n; i++)
		if (n%i == 0) {
			v.clear();
			int len = n/i,ok = 1;
			for (int j=0; j<n; j+=len) {
				int yes = 0;
				for (int k=0; k<len; k++) {
					if (strcmp(s[j+k],"unknown") == 0) continue;
					if (yes == 0) {
						if (v.find(s[j+k]) != v.end()) ok = 0;
						v.insert(s[j+k]);
						yes = 1;	
					}
					else {
						if (v.find(s[j+k]) == v.end()) ok = 0;
					}
				}
				if (ok == 0) break;
			}
			if (ok) {
				if (done) {
					printf(" ");
				}	
				done = 1;
				printf("%d",i);
			}
		}
	if (!done) {
		puts("Igor is wrong.");	
	}
	else puts("");
  return 0;
}

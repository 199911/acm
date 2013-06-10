#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

int tc,n;
char s[100];

int doit(int a) {
	//printf("%d\n",a);
	if (a == 0) return 1;
	int fr=0,cur=-1;
	for (int i=0; i<=n; i++) {
		if (i == n) {
			int ta = a,cnt = 0;
			//printf("** %d %d\n",fr,i-1);
			for (int j=fr; j<i; j++)
				if ((1<<j) & ta) {
					ta -= (1<<j);
					cnt++;
				}
			if (cnt >= 2) {
				int ok = doit(ta);
				if (ok) return 1;
			}
			break;
		}	
		
		if ((1<<i) & a) {
			//printf("  %d\n",i);
			if (s[i]-'a' != cur) {
				if (cur != -1) {
					int ta = a,cnt = 0;
					//printf("%d %d\n",fr,i-1);
					for (int j=fr; j<i; j++)
						if ((1<<j) & ta) {
							cnt++;
							ta -= (1<<j);
						}
					if (cnt >= 2) {
						int ok = doit(ta);
						if (ok) return 1;
					}
				}
				fr = i;
				cur = s[i]-'a';
			}	
			
		}
	}
	return 0;
	
}

int main() {
	scanf("%d",&tc);
	while (tc--) {
	//	memset(dp,-1,sizeof(dp));
		scanf("%s",s);
		n = strlen(s);
		printf("%d\n",doit((1<<n)-1));
	}
  return 0;
}

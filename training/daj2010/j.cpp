#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

struct S {
	int a,b;	
} s[10005];

int tc,n;
char ts[10005];
set<int> v;
set<int>::iterator it;

int cmp(S a,S b) {
	return a.a < b.a;	
}

int main() {
	scanf("%d",&tc);
	while (tc--) {
		scanf("%d",&n);
		for (int i=0; i<n; i++) {
			scanf("%s",ts);
			int len = strlen(ts);
			int cur = 0,fg = 0;
			//printf("%s\n",ts);
			for (int j=1; j<len; j++)
				if (ts[j] >= '0' && ts[j] <= '9') {
					cur *= 10; cur += ts[j]-'0';	
				}
				else {
					if (fg == 0) {
						if (ts[j] == 'E') s[i].a = 3000000-cur;
						else s[i].a = cur;
						fg = 1;
					}
					else {
						if (ts[j] == 'E') s[i].b = 3000000-cur;
						else s[i].b = cur;
					}
					cur = 0;
				}
			//printf("%d %d\n",s[i].a,s[i].b);
		}
		sort(s,s+n,cmp);
		
		v.clear();
		for (int i=0; i<n; i++) {
			int ti = s[i].b;
			it = upper_bound(v.begin(),v.end(),ti);
			if (it == v.begin()) {
				v.insert(ti);	
			}
			else {
				it--;
				v.erase(it);
				v.insert(ti);	
			}
		}
		printf("%d\n",v.size());
	}
	return 0;
}

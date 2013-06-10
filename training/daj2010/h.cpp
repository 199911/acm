#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

struct S {
	int a,d;	
} s[555];

int tc,n;
priority_queue<pair<int,int> > pq1;
priority_queue<int> pq2;
int ot[555],b[555],a[555];

bool cmp(S a,S b) {
	if (b.d != a.d) return a.d < b.d;
	return a.a < b.a;	
}

int main() {
	scanf("%d",&tc);
	while (tc--) {
		scanf("%d",&n);
		for (int i=0; i<n; i++)
			scanf("%d%d",&s[i].a,&s[i].d);
		sort(s,s+n,cmp);
		
		int cur = 0;	
		for (int i=0; i<n; i++) {
			cur += s[i].a;
			ot[i] = cur;
			//printf("%d <> %d\n",cur,s[i].d);
		}
		
		int ret = (1<<30);
		for (int i=0; i<n; i++) {
			while (!pq1.empty()) pq1.pop();
			while (!pq2.empty()) pq2.pop();
			for (int j=i+1; j<n; j++) pq1.push(make_pair(max(0,ot[j]-s[j].d),j));
			for (int j=0; j<i; j++) b[j] = max(0,ot[j]-s[j].d);
			sort(b,b+i);
			int ca = 0;
			
			
			for (int j=i; j<n; j++) {
				while (!pq1.empty() && pq1.top().second <= j) pq1.pop();
				if (j > i) pq2.push(max(0,ot[j]-s[j].d-s[i].a));
				ca = 0;
				if (i > 0) a[ca++] = b[i-1];
				if (i > 1) a[ca++] = b[i-2];
				pair<int,int> tp; int ti;
				if (!pq1.empty()) {
					//puts("hi");
					a[ca++] = pq1.top().first;
					tp = pq1.top();
					pq1.pop();
					
					while (!pq1.empty() && pq1.top().second <= j) pq1.pop();
					if (!pq1.empty()) {	
						a[ca++] = pq1.top().first;
					}
					pq1.push(tp);	
				}
				if (!pq2.empty()) {
					a[ca++] = pq2.top();
					ti = pq2.top();
					pq2.pop();
					if (!pq2.empty()) a[ca++] = pq2.top();
					pq2.push(ti);	
				}
				a[ca++] = max(0,ot[j]-s[i].d);
				
				//printf("%d,%d: ",i,j);
				///for (int k=0; k<ca; k++) printf("%d ",a[k]);
				//puts("");
				
				sort(a,a+ca);
				ret = min(ret,a[ca-1]+a[ca-2]);
				
			}	
		}
		printf("%d\n",ret);
		
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

struct S {
	int t,id;
	int ans;	
} p[105];

int hh,mm,ss,n,m,t1,t2,t3,t4;
queue<int> q1,q2;

bool cmp(S x,S y) {
	if (x.t == y.t) {
		return x.id > y.id;	
	}	
	return x.t < y.t;
}

bool idcmp(S x,S y) {
	return x.id < y.id;
}

int main() {
	scanf("%d%d%d%d",&t1,&t2,&t3,&t4);
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		// takeoff
		scanf("%d:%d:%d",&hh,&mm,&ss);
		p[i].t = hh*3600+mm*60+ss;
		p[i].id = i;	
	}
	scanf("%d",&m);
	for (int i=0; i<m; i++) {
		// landing
		scanf("%d:%d:%d",&hh,&mm,&ss);
		p[i+n].t = hh*3600+mm*60+ss;
		p[i+n].id = i+n;	
	}
	
	sort(p,p+n+m,cmp);
	
	int cur = p[0].t,nt1,nt2,at = 0;
	int done = 0;
	nt1 = nt2 = cur;
	while (done < n+m) {
		
		while (at < n+m && p[at].t <= cur) {
			if (p[at].id < n) q2.push(at);
			else q1.push(at);
			at++;	
		}
		//printf("%d: %d (%d,%d) (%d,%d)\n",done,cur-p[0].t,q1.size(),q2.size(),nt1,nt2);
		
		nt1 = max(nt1,cur);
		nt2 = max(nt2,cur);
		
		if (!q1.empty()) {
			// must land
			if (cur < nt1) {
				if (at < n+m) cur = min(nt1,p[at].t); 
				else cur = nt1;
				continue;	
			}
			int tp = q1.front(); q1.pop();
			p[tp].ans = cur; done++;
			nt1 = p[tp].ans + t4;
			nt2 = p[tp].ans + t3;
			cur = min(p[at].t,nt1);
			continue;
		}
		
		if (!q2.empty()) {
			if (cur < nt2) {
				if (at < n+m) cur = min(nt2,p[at].t);
				else cur = nt2;
				continue;	
			}
			int tp = q2.front(); q2.pop();
			p[tp].ans = cur; done++;
			nt1 = p[tp].ans + t2;
			nt2 = p[tp].ans + t1;
			cur = min(p[at].t,nt2);
			continue;
		}
		
		cur = p[at].t;
	}
	
	sort(p,p+n+m,idcmp);
	for (int i=0; i<n+m; i++) {
		printf("%02d:%02d:%02d\n",p[i].ans/3600,(p[i].ans%3600)/60,p[i].ans%60);
	}
  return 0;
}

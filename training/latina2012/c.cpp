#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int n,ans;
char ts[88];
string s[100005];

void doit(int fr,int to,int pos) {
	if (pos == 0) {
		ans += to-fr+1;
		int now = fr;
		for (int i=fr; i<=to; i++)
			if (s[now][pos] != s[i][pos]) {
				doit(now,i-1,pos+1);
				now = i;	
			}
		doit(now,to,pos+1);
		return;
	}
	if (fr == to) return;
	if (s[fr].length() > pos && s[fr][pos] == s[to][pos]) {
		doit(fr,to,pos+1);
		return;	
	}
	if (s[fr].length() == pos) {
		ans += to-fr;
		int now = fr+1;
		for (int i=fr+1; i<=to; i++)
			if (s[now][pos] != s[i][pos]) {
				doit(now,i-1,pos+1);
				now = i;	
			}
		doit(now,to,pos+1);
		return;
	}
	else {
		ans += to-fr+1;
		int now = fr;
		for (int i=fr; i<=to; i++)
			if (s[now][pos] != s[i][pos]) {
				doit(now,i-1,pos+1);
				now = i;	
			}
		doit(now,to,pos+1);
		return;
	}
}

int main() {
	
	while (scanf("%d",&n) == 1) {
		ans = 0;
		for (int i=0; i<n; i++) {
			scanf("%s",ts);
			s[i] = ts;
		}
		sort(s,s+n);
		doit(0,n-1,0);
		printf("%.2f\n",ans*1.0/n);
	}
  return 0;
}

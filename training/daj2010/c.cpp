#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long 

int tc,n;
string ret[8888];
int cr = 0,v[55],ga[7][7],gc[7][27];


void doit(int at) {
	if (at == 5) {
		int ok = 1;
		for (int i=0; i<5; i++)
			if (gc[i][v[i]] == 0) ok = 0;
		if (ok) {
			string ss = "";
			for (int i=0; i<5; i++)
				ss += v[i]+'A';
			//printf("%s\n",ss.c_str());
			ret[cr++] = ss;
		}
		return;
	}
	for (int i=0; i<6; i++) {
		v[at] = ga[at][i];
		//printf("%d,%d: %c\n",at,i,v[at]+'A');
		doit(at+1);
	}
}

int main() {
	scanf("%d",&tc);
	while (tc--) {
		cr = 0;
		scanf("%d",&n);
		for (int i=0; i<6; i++) {
			char ts[11];
			scanf("%s",ts);
			for (int j=0; j<5; j++)
				ga[j][i] = ts[j]-'A';
		}
		for (int i=0; i<5; i++)
			sort(ga[i],ga[i]+6);
		memset(gc,0,sizeof(gc));
		for (int i=0; i<6; i++) {
			char ts[11];
			scanf("%s",ts);
			for (int j=0; j<5; j++)
				gc[j][ts[j]-'A'] = 1;
		}
		doit(0);
		sort(ret,ret+cr);
		cr = unique(ret,ret+cr)-ret;
		if (n-1 >= cr) {
			puts("NO");	
		}
		else {
			printf("%s\n",ret[n-1].c_str());	
		}
	}
  return 0;
}

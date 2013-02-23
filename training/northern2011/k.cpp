#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

void F(int ind, int t, int time){
	f[time]++;
	s[ind][t] = time;
}

int main() {
	scanf("%d%d%d", &delay, &cap, &n);
	while (!Q.empty()) Q.pop();
	
	FOR(i, 0, n){
		scanf("%d", &tmp);
		Q.push(Seg(i, tmp - delay, tmp - 1));
	}
	
	FOE(i, 0, 1000) f[i] = 0;
	
	pre = -1;
	
	while (!Q.empty()){
		ind = Q.top().x;
		a = Q.top().a;
		b = Q.top().b;
		Q.pop();
		if (a > pre){
			F(ind, 0, b - 1);
			F(ind, 1, b);
		}
		else {
			ok = 0;
			FOE(i, a, b) if (f[i] > 0 && f[i] + 1 <= cap){
				ok++;
				F(ind, 0, i);
				nex = i;
				break;
			}
			if (ok == 1){
				FOE(i, nex + 1, b) if (f[i] > 0 && f[i] + 1 <= cap){
					ok++;
					F(ind, 1, i);
					break;
				}
			}
			
			if (ok == 0){
				F(ind, 0, b - 1);
				F(ind, 1, b);
			}
			else if (ok == 1){
				F(ind, 1, b);
			}		
		}
	}
	
	AC = 0;
	FOE(i, 0, 1000) if (f[i] > 0) AC++;
	
	
	return 0;
}

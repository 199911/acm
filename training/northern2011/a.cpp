#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int h, t, v, x;
double mn, mx;

int main() {
	scanf("%d%d%d%d", &h, &t, &v, &x);
	mn = max(0.0, (h - x * t) * 1.0 /(v - x));
	mx = min(t*1.0, h*1.0/x);
	printf("%.9f %.9f\n", mn, mx);
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int n,v[666][666];
int qx[400000],qy[400000],q1,q2;
char s[777][777];

bool sx(int a) {
	if (a >= 0 && a < 2*n-1) return true;
	return false;	
}
bool sy(int a) {
	if (a >= 0 && a < n) return true;
	return false;	
}

bool rx(int a) {
	if (a >= 0 && a < 2*n) return true;
	return false;	
}
bool ry(int a) {
	if (a >= 0 && a < 2*n+1) return true;
	return false;	
}

void ins(int x,int y) {
	qx[q2] = x; qy[q2] = y; q2++; 
	v[x][y] = 1;	
}

void doit(int x,int y) {
	q1 = q2 = 0;
	ins(x,y);
	while (q1 < q2) {
		x = qx[q1]; y = qy[q1]; q1++;
		
		if ((x+y)%2 == 1) {
			//printf("%d,%d\n",x,y);	
			//x-1,y/2
			if (sx(x-1) && sy(y/2)) {
				if (s[x-1][y/2] == 'H') {
					if (rx(x) && ry(y+1) && v[x][y+1] == 0)
						ins(x,y+1);	
				}
				else {
					if (rx(x-1) && ry(y) && v[x-1][y] == 0)
						ins(x-1,y);	
				}
			}
			else {
				if (rx(x) && ry(y+1) && v[x][y+1] == 0)
					ins(x,y+1);	
				if (rx(x-1) && ry(y) && v[x-1][y] == 0)
					ins(x-1,y);
			}
			
			//x,(y+1)/2-1
			if (sx(x) && sy((y+1)/2-1)) {
				if (s[x][(y+1)/2-1] == 'H') {
					if (rx(x) && ry(y-1) && v[x][y-1] == 0)
						ins(x,y-1);	
				}
				else {
					if (rx(x+1) && ry(y) && v[x+1][y] == 0)
						ins(x+1,y);	
				}
			}
			else {
				if (rx(x) && ry(y-1) && v[x][y-1] == 0)
					ins(x,y-1);	
				if (rx(x+1) && ry(y) && v[x+1][y] == 0)
					ins(x+1,y);	
			}
		}
		else {
			//printf("%d,%d\n",x,y);
			//x-1,(y+1)/2-1
			if (sx(x-1) && sy((y+1)/2-1)) {
				if (s[x-1][(y+1)/2-1] == 'H') {
					if (rx(x) && ry(y-1) && v[x][y-1] == 0)
						ins(x,y-1);	
				}
				else {
					if (rx(x-1) && ry(y) && v[x-1][y] == 0)
						ins(x-1,y);	
				}
			}
			else {
				if (rx(x) && ry(y-1) && v[x][y-1] == 0)
					ins(x,y-1);	
				if (rx(x-1) && ry(y) && v[x-1][y] == 0)
					ins(x-1,y);
			}
			
			//x,y/2	
			if (sx(x) && sy(y/2)) {
				if (s[x][y/2] == 'H') {
					if (rx(x) && ry(y+1) && v[x][y+1] == 0)
						ins(x,y+1);	
				}
				else {
					if (rx(x+1) && ry(y) && v[x+1][y] == 0)
						ins(x+1,y);	
				}
			}
			else {
				if (rx(x) && ry(y+1) && v[x][y+1] == 0)
					ins(x,y+1);	
				if (rx(x+1) && ry(y) && v[x+1][y] == 0)
					ins(x+1,y);	
			}
		}
	}
	
	
}

int main() {
	while (scanf("%d",&n) == 1) {
		for (int i=0; i<2*n-1; i++)
			scanf("%s",s[i]);
		CLR(v,0);
		int ans = 0;
		for (int i=0; i<2*n; i++)
			for (int j=0; j<2*n+1; j++)
				if (v[i][j] == 0) {
					//printf("ins %d\n",ans);
					doit(i,j);
					ans++;
				}
		printf("%d\n",ans-1);
	}
  return 0;
}

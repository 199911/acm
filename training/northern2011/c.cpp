#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

int a[33], b[33], c[33], n;
double dt[22], dd[22], p[22], t[22]; 

double ret[1<<10],pp[1<<10];
double expect[2000];
int v[2000];

int f( int i, int x ) {
  return ( a[i] * x * x + b[i] * x + c[i] ) % 11;
}

void doit(int st) {
	if (ret[st] > -1e-9) return;
	if (st == 0) {
		ret[st] = 0;
		pp[st] = 1;
		return;
	}
	
	pp[st] = 0;
	ret[st] = 0;
	double totp = 0;
	for (int i=0; i<10; i++)
		if ((1<<i) & st) {
			doit(st-(1<<i));
			double tp = 0,np = 0;
			for (int j=0; j<10; j++)
				if ((1<<j) & (st-(1<<i))) {
					tp += p[j];	
				}
				else np += p[j];
			totp += pp[st-(1<<i)]*1.0*p[i]/np;
		}
	
	for (int i=0; i<10; i++)
		if ((1<<i) & st) {
			double tp = 0,np = 0;
			for (int j=0; j<10; j++)
				if ((1<<j) & (st-(1<<i))) {
					tp += p[j];	
				}
				else np += p[j];
			
			ret[st] += pp[st-(1<<i)]*1.0*p[i]/np/totp * (ret[st-(1<<i)] + 1.0/(1-tp) );
			pp[st] += pp[st-(1<<i)]*1.0*p[i]/np;
			//printf("   %f %f %f\n",tp,ret[st],pp[st]);
		}

	//printf("%d: %f %f\n",st,ret[st],pp[st]);
}

double F(int mask){
	if (mask == (1<<10) - 1) return 0.0;
	if (v[mask]) return expect[mask];
	v[mask] = 1;
	expect[mask] = 0.0;
	double sp = 0.0;
	FOR(i, 0, 10)
		if (((1<<i)|mask) == mask) sp += p[i];
	FOR(i, 0, 10)
		if ((1<<i) & mask){ }
		else {
			double E = F(mask|(1<<i));
			expect[mask] += (E + 1.0/p[i]) * 1.0/(1 - sp);	
		}
	return expect[mask];
}

int main() {
  scanf( "%d", &n );
  REP( i, n ) scanf( "%d", &a[i] );
  REP( i, n ) scanf( "%d", &b[i] );
  REP( i, n ) scanf( "%d", &c[i] );

  REP( i, 11 ) dt[i] = 0;
  REP( i, 10 ) dt[f(0, i)] += 0.1;

  FOR( i, 1, n ) {
    REP( j, 11 ) t[j] = 0;
    REP( j, 10 ) t[f(i, j)] += 0.1;
    REP( j, 11 ) dd[j] = 0;
    REP( j, 11 ) REP( k, 11 ) {
      dd[j * k % 11] += dt[j] * t[k];
    }
    REP( j, 11 ) dt[j] = dd[j];
  }

  REP( i, 10 ) p[i] = 0;
  REP( i, 11 ) p[i % 10] += dt[i];
  //REP( i, 10 ) printf( "%f\n", p[i] );
  
  for (int i=0; i<10; i++)
  	if (p[i] < 1e-9) { puts("-1"); return 0; }
  
  for (int i=0; i<(1<<10); i++)
  	ret[i] = -1;
  doit((1<<10)-1);
  //printf("%.9f\n",ret[(1<<10)-1]);
  printf("%.9f\n", F(0));
  return 0;
}

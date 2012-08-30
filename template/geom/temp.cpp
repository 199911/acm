#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn = 1005;
typedef double db;
const db EPS = 1e-6;
typedef pair<db, db> PDD;
int x[ maxn ], y[ maxn ], r[ maxn ];
int nx[ maxn ], ny[ maxn ], nr[ maxn ];
int xl[ maxn ], xr[ maxn ];

int s[ maxn ];
inline bool cmp( int a, int b) {
  if( x[ a ] - r [ a ] == x[ b ] - r [ b ] ) return x[ a ] + r[ a ] < x[ b ] + r [ b ];
  return x[ a ] - r[ a ] < x[ b ] - r [ b ];
}
inline bool cmp0(int a, int b){return r[ a ] > r [ b ];}
int n;
int L, R;
PDD se[ maxn ];
inline db f( db v){
  int sz = 0, i, j ;
  db ret = 0.0;
  for(i = L; i < R; ++ i){
    if( v <= xl[ i ] || v >= xr[ i ] ) continue;
    j = s[ i ];
    db d = sqrt(r[ j ]- (v - x [ j ]) * (v - x[ j ]));
    se[ sz ].first = y[ j ] - d;
    se[ sz ].second = y[ j ] +  d;
    ++ sz;   
  }
  sort( se, se + sz);
  for(i = 0; i < sz; ++ i){
    db nowl , nowr;
    nowl = se[ i ].first;
    nowr = se[ i ].second;
    for( j = i + 1; j < sz; ++ j) if(se[ j ].first > nowr) break;
    else nowr = max( nowr, se[ j ].second);
    ret += nowr - nowl;
    i = j - 1;      
  }
  return ret;
}
#define fs(x) ((x) < 0 ? (-(x)) : (x))
inline db rsimp( db l,db m, db r, db sl, db sm, db sr,db tot){
  db m1 = (l + m) * 0.5, m2 = (m + r) * 0.5;
  db s0 = f( m1), s2 = f( m2);
  db gl = (sl + sm + s0 + s0 + s0 + s0)*(m-l), gr = (sm + sr + s2 + s2 + s2 + s2)*(r-m);
  if( fs(gl + gr - tot) < EPS) return gl + gr;
  return rsimp( l, m1, m, sl, s0, sm, gl) + rsimp( m, m2,r, sm, s2, sr, gr);         
}

bool get(){ 
  if(1 != scanf("%d", &n)) return 0;
  int i, j = 0, k;
  for(i = 0; i < n; ++ i) scanf("%d%d%d", x + i, y + i, r + i), s[ i ] = i;
  sort( s, s + n, cmp0);
  for(i = 0; i < n; ++ i){
    for(k = 0; k < j; ++ k)
      if( (nx [ k ] - x [s[i]]) * (nx [ k ] - x [s[i]])  + (ny [ k ] - y [s[i]]) *(ny [ k ] - y [s[i]])  
          <= (nr[ k ] - r[ s[ i ] ]) * (nr[ k ] - r[ s[ i ] ]) ) break;
    if( k == j) {
      nx[ j ] = x[ s[ i ] ];
      ny[ j ] = y[ s[ i ] ];
      nr[ j ] = r[ s[ i ] ];
      s[ j ] = j;
      j ++;    
    }      
  }
  n = j;
  for(i = 0; i < n; ++ i) x[ i ] = nx[ i ], y[ i ] = ny[ i ], r[ i ] = nr[ i ];
  return 1;
}

void work(){
  sort( s, s + n, cmp) ;
  db lo, hi, ans = 0.0;
  int i, j;
  for(i = 0; i < n; ++ i) xl[ i ] = x[ s[ i ] ] - r[ s[ i ] ], xr[ i ] = x[ s[ i ] ] + r[ s[ i ] ], r[ s[i] ] *= r[ s[i] ];
  for(i = 0; i < n; ++ i){
    int ilo, ihi;
    ilo = xl[ i ];
    ihi = xr[ i ];
    for(j = i + 1; j < n; ++ j) {
      if( xl[ j ] > ihi ) break;
      ihi = max( ihi, xr[ j ]);
    }
    db lo = ilo;
    db hi = ihi;      
    L = i;
    R = j;
    db mid = (lo + hi) * 0.5;
    db sl = f(lo), sm = f(mid), sr = f(hi);
    db tot = sl + sr + sm + sm + sm + sm;
    ans += rsimp( lo, mid , hi, sl, sm , sr, tot );
    i = j - 1;
  }
  printf("%.3f\n", ans / 6.0);
}

int main(){
  while( get() ) work();
  return 0;
}

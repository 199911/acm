#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

#define N 222

int adj[N][N], n, m;
int cmp[N], idg[N];

void eat() {
  CLR( adj, 0 );
  cin >> n;
  REP( i, n ) {
    cin >> cmp[i];
    cmp[i]--;
  }

  CLR( idg, 0 );

  REP( i, n ) {
    cin >> idg[i];
    REP( j, idg[i] ) {
      int x;
      cin >> x;
      x--;
      adj[x][i] = 1;
    }
  }
}

#define DIS(a,b) (((b+3)-(a))%3)

int main() {
  eat();


  int ans = 1<<29;

  REP( st, 3 ) {
    int tot = 0;
    int ptr = -1;
    REP( i, n ) {
      if ( st == cmp[i] && idg[i] == 0 ) ptr = i;
    }
    if ( ptr == -1 ) continue;

    int d[N];

    CLR( d, 0 );

    tot = 1;

    while ( true ) {
      d[ptr] = 1;
      // find next
      REP( i, n ) {
        if ( adj[ptr][i] ) {
          idg[i]--;
        }
      }
      int nt = -1;
      REP( i, n ) {
        if ( idg[i] == 0 && !d[i] ) {
          if ( nt == -1 ) nt = i;
          else {
            if ( DIS(cmp[ptr],cmp[i]) < DIS(cmp[ptr], cmp[nt]) ) nt = i;
          }
        }
      }

      if ( nt == -1 ) break;

      tot += DIS(cmp[ptr], cmp[nt]);
      tot++;

      ptr = nt;
    }

    gmin(ans, tot);

  }

  printf( "%d\n", ans );
  return 0;
}

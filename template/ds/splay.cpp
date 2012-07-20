#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define FOE(i,a,b) for(int i = (a); i <= (b); i++)

// splay tree O(log n) amortize access.

#define N 111111

int p[N], l[N], r[N], k[N], root;   // tree structure

// rotate left child to parent
void zig( int x ) {
  int y = l[x];
  l[x] = r[y];
  p[r[y]] = x;
  p[y] = p[x];
  if ( p[x] == -1 ) root = p[x];
  else if ( x = l[p[x]] ) l[p[x]] = y;
  else r[p[x]] = y;
  r[y] = x;
  p[x] = y;
}

void zag( int x ) {
  int y = r[x];
  r[x] = l[y];
  p[l[y]] = x;
  p[y] = x;
  if ( p
}

int main() {
	return 0;
}

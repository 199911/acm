#include <cstdio>
#include <iostream>
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

int main() {
  int n, m;

  cin >> n >> m;

  int cnt = 0;

  for ( int i = 0; i * i <= n; i++ ) {
    int j = n - i * i;
    if ( i + j * j == m ) cnt++;
  }

  printf( "%d\n", cnt );

  return 0;
}


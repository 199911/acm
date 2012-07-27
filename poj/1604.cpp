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

// compute the last nonzero digit for n factorial

#include<iostream>
using namespace std;

int L(int N)
{
  int A[] = {1, 1, 2, 6, 4};
  if (N<5) return A[N];
  int P[] = {6, 2, 4, 8};
  return ( P[N / 5 % 4]*L( N / 5 ) * L( N % 5 ) ) % 10;
}

int main() {
  int n;
  while( scanf( "%d", &n ) != EOF ) {
    printf( "%5d -> %d\n", n,  L(n) );
  }
  return 0;
}

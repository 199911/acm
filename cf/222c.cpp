#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <bitset>
#include <map>
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

#define N 10000005

int fact[N];

void seive( ) {
  REP( i, N ) fact[i] = i;
  fact[0] = fact[1] = 0;
  for( int i = 2; i < N; i++ ) {
    if ( fact[i] == i ) {
      for( int j = i + i; j < N; j += i ) 
        if ( fact[j] == j ) fact[j] = i;
    }
  }
}

void reduce( int A[], int n ) {
  for( int i = n; i >= 2; i-- ) 
    if ( A[i] && fact[i] != i) {
      A[fact[i]] += A[i];
      A[i / fact[i]] += A[i];
      A[i] = 0;
    }
}

void intersect( int A[], int n, int B[], int m, int R[], int &rn ) {
  rn = 0;
  for( int i = 2; i <= n && i <= m; i++ ) {
    R[i] = min( A[i], B[i] );
    if ( R[i] ) rn = i;
  }
}

int T[N];
void divide( vector<int> &V, int R[], int rn ) {
  CLR( T, 0 );
  FOE( i, 2, rn ) T[i] = R[i];
//  REP( i, rn + 1 ) 
//    if( T[i] ) printf( "%d: %d\n", i, T[i] );
  for( vector<int>::iterator it = V.begin(); it != V.end(); it++ ) {
    int &x = *it, t = x;
//    printf( "%d==>\n", x );
    while( t > 1 ) {
      if ( T[fact[t]] ) {
//        printf( "%d--->%d\n", fact[t], T[fact[t]] );
        x /= fact[t];
        T[fact[t]]--; 
      }
      t /= fact[t];
    }
//    printf( "to %d\n", x );
  }
}

int an, bn, A[N], B[N], R[N], am, bm, rm;
vector<int> nu, de;

int main() {
  seive();
  scanf( "%d%d", &an, &bn );
  CLR( A, 0 );
  CLR( B, 0 );
  int am = -1, bm = -1;
  REP( i, an ) {
    int x;
    scanf( "%d", &x );
    am = max( am, x );
    A[x]++;
    nu.push_back( x );
  }
  REP( i, bn ) {
    int x;
    scanf( "%d", &x );
    bm = max( bm, x );
    de.push_back( x );
    B[x]++;
  }

  reduce( A, am );
  /*
  REP( i, am ) 
    if( A[i] ) printf( "%d: %d\n", i, A[i] );
  puts( "" );
  */
  reduce( B, bm );
  /*
  REP( i, bm ) 
    if( B[i] ) printf( "%d: %d\n", i, B[i] );
  puts( "" );
  */
  intersect( A, am, B, bm, R, rm );
//  REP( i, rm + 1 ) 
//    if( R[i] ) printf( "%d: %d\n", i, R[i] );

  divide( nu, R, rm );
  divide( de, R, rm );

  printf( "%d %d\n", nu.size(), de.size() );
  for( int i = 0; i < nu.size(); i++ ) 
    printf( "%d%s", nu[i], i == nu.size() - 1 ? "\n" : " " );
  for( int i = 0; i < de.size(); i++ ) 
    printf( "%d%s", de[i], i == de.size() - 1 ? "\n" : " " );

  return 0;
}

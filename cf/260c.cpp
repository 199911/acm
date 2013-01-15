#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n, mi, x;
long long a[100005], m,  cnt;

int main() {
  cin >> n >> x;
  x--;
  m = 1<<30;
  for( int i = 0; i < n; i++) cin >> a[i];
  for( int i = 0; i < n; i++ ) {
    int j =  (x - i + n) % n;
    if ( a[j] < m ) {
      m = a[j];
      mi = j;
    }
  }
  m++;
  cnt = 0;

  for( int i = 0; i < n; i++ ) {
    int j = ( x - i + n ) % n;
    if ( j == mi ) m--;
    cnt += m;
    a[j] -= m;
  }
  a[mi] = cnt;

  for( int i = 0; i < n; i++ ) {
    cout << a[i];
    if ( i != n - 1 ) cout << " ";
    else cout << endl;
  }
  return 0;
}

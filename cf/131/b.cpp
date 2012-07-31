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
  int n;
  cin >> n;
  int d[111111], s = 0;

  for ( int i = 0; i < n; i++ ) {
    cin >> d[i];
    s += d[i];
  }
  
  sort( d, d + n );

  if ( d[0] != 0 ) {
    printf( "-1\n" );
    return 0;
  }

  int res[4] = {};
  for ( int i = 0; i < n; i++ ) {
    for ( int k = 0; k < 3; k++ ) {
      res[(k + d[i]) % 3] |= res[k];
    }
    res[d[i] % 3] = 1;
  }

  if ( !res[0] ) {
    puts( "-1" );
    return 0;
  }

  if ( s % 3 == 0 ) {
    if ( s == 0 ) {
      puts( "0" );
    } else {
      for ( int i = n - 1; i >= 0; i-- ) printf( "%d", d[i] );
      puts( "" );
    }
  } else {
    int cnt[3] = {};
    for ( int i = 0; i < n; i++ ) {
      cnt[d[i] % 3]++;
    }

    if ( s % 3 == 2 && cnt[2] == 0 ) {
      for ( int i = 0, lf = 2; i < n; i++ ) {
        if ( lf && d[i] % 3 == 1 ) {
          d[i] = -1;
          lf--;
        }
      }
    } else if ( s % 3 == 1 && cnt[1] == 0 ) {
      for ( int i = 0, lf = 2; i < n; i++ ) {
        if ( lf && d[i] % 3 == 2 ) {
          d[i] = -1;
          lf--;
        }
      }
    } else {
      for ( int i = 0; i < n ; i++ ) {
        if ( d[i] % 3 == s % 3 ) {
          d[i] = -1;
          break;
        }
      }
    }

    int ns = 0;
    for ( int i = n - 1; i >= 0; i-- ) {
      if ( d[i] != -1 ) ns += d[i];
    }

    if ( ns ) {
      for ( int i = n - 1; i >= 0; i-- ) {
        if ( d[i] != -1 ) {
          printf( "%d", d[i] );
        }
      }
      puts( "" );
    } else {
      puts( "0" );
    }
  }


	return 0;
}

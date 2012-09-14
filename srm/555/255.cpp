#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

int ok( string s ) {
  long long x = 0;
  for( int i = 0; i < s.length(); i++ ) {
    x *= 2;
    x += s[i] - '0';
  }
  while( x > 1 ) {
    if ( x % 5 ) return false;
    x /= 5;
  }
  if ( x == 1 ) return true;
  return false;
}

int getmin( string s ) {
  int dp[55];
  dp[s.length()] = 0;
  for( int i = s.length() - 1; i >= 0; i-- ) {
    dp[i] = 1<<29;
    if ( s[i] == '0' ) continue;
    for( int j = 1; i + j <= s.length(); j++ ) {
      if( ok( s.substr(i, j) ) ) {
        dp[i] = min( dp[i], dp[i + j] + 1);
      }
    }
  }
  if ( dp[0] >= 1 << 29 ) return -1;
  return dp[0];
}

int main() {
  string s;
  cin >> s;
  cout << getmin( s ) << endl;
  return 0;
}

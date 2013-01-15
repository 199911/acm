#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;


string a( "BWBWBWBW" ), b( "WBWBWBWB" ); 

int main() {
  int f = 1;
  for( int i = 0; i < 8; i++ ) {
    string s;
    cin >> s;
    if ( s != a && s != b ) f = 0;
  }
  printf( "%s\n", f ? "YES" : "NO" );
  return 0;
}

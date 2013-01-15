#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

multimap<int,int> mp[2];
int n;

int main() {
  cin >> n;
  for( int i = 0; i < n; i++ ) {
    int c, s;
    cin >> c >> s;
    mp[c].insert( make_pair( s, i ) );
  }

  for( int i = 0; i < n - 1; i++ ) {
    multimap<int,int>::iterator it = mp[0].begin(), jt = mp[1].begin();
    if ( it->first < jt->first || it->first == jt->first && mp[0].size() > mp[1].size() ) {
      cout << it->second + 1 << " " << jt->second + 1 << " " << it->first << endl;
      int s = jt->first - it->first, nd = jt->second;
      mp[0].erase( it );
      mp[1].erase( jt );
      mp[1].insert( make_pair( s, nd ) );
    } else {
      cout << it->second + 1 << " " << jt->second + 1 << " " << jt->first << endl;
      int s = it->first - jt->first, nd = it->second;
      mp[0].erase( it );
      mp[1].erase( jt );
      mp[0].insert( make_pair( s, nd ) );
    }
  }
  return 0;
}

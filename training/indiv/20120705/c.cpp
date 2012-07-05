#include <cstdio>
#include <cstring>
using namespace std;

bool yes[10111];

int ds(int x) {
  int ret = 0;
  while(x) {
    ret += x % 10;
    x /= 10;
  }
  return ret;
}

int main(){
  memset(yes, 0, sizeof(yes));
  for(int i = 0; i <= 10000; i++) {
    yes[i+ds(i)] = true;
  }
  for(int i = 1; i <= 10000; i++) {
    if( !yes[i] ) printf("%d\n", i);
  }
  return 0;
}

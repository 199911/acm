#include <cstdio>
#include <cstring>
using namespace std;

int main(){
  long long a, cnt = 0;
  scanf( "%lld", &a );
  for(int i = 1; ( i + 1 ) * i <= 2 * a; i++) {
    if ( i & 1 ) {
      if ( a % i == 0 ) cnt++;
    } else {
      if ( a % i == i / 2 ) cnt++; 
    }
  }
  printf("%lld\n", cnt);
  return 0;
}

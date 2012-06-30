#include <cstdio>
#include <cstring>
using namespace std;

void print(char *str) {
  int ans = 0, k = 128;
  for(int i = 0; i < 8; i++) {
    ans += ( str[i] - '0' ) * k;
    k >>= 1;
  }
  printf("%d", ans);
}

int main(){
  int n;
  scanf("%d", &n);
  while(n--) {
    char str[100];
    scanf("%s", str);
    print(str);
    printf(".");
    print(str+8);
    printf(".");
    print(str+16);
    printf(".");
    print(str+24);
    puts("");
  }
  return 0;
}

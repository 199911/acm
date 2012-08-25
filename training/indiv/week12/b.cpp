#include <cstdio>

int main() {
  int n;
  while (scanf( "%d", &n ) != EOF  ) {
    int res = 1 % n, cnt = 1;
    res %= n;
    while ( res != 0 ) {
      res *= 10;
      res ++;
      res %= n;
      cnt++;
    }
    printf( "%d\n", cnt );
  }
  return 0;
}

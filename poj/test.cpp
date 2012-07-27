#include <cstdio>
using namespace std;

const int inv[] = {0, 1, 0, 7, 0, 0, 0, 3, 0, 9};
const int twos[] = {6, 2, 4, 8};
const int ms[] = {1, 1, 1, 3, 3, 3, 3, 1, 1, 9,
  9, 9, 9, 7, 7, 7, 7, 9, 9, 1};

int N, M;

bool init(){
  return scanf("%d%d", &N, &M)!=EOF;
}

int calc(int n){
  if(n <= 1){
    return 1;
  }

  return ms[n%20] * calc(n/2) * calc(n/5) * inv[calc(n/10)] % 10;
}

int fact2(int n){
  int ret = 0;
  for(;n;n/=2){
    ret += n / 2;
  }
  return ret;
}

int fact5(int n){
  int ret = 5;
  for(;n;n/=5){
    ret += n / 5;
  }
  return ret;
}

int solve(){
  if(N == 0){
    return 1;
  }

  int two = fact2(N) - fact2(N - M);
  int five = fact5(N) - fact5(N - M);
  int m = calc(N) * inv[calc(N - M)] % 10;

  if(two == five){
    return m;
  }
  if(two > five){
    return m * twos[(two - five) % 4] % 10;
  }
  else {
    return 5;
  }
}

int main(){
  for(;init();){
    printf("%d\n", solve());
  }

  return 0;
}

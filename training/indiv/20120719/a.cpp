#include <cstdio>
#include <cstring>

using namespace std;

int main(){
  char a[100], st[100];
  scanf( "%s" , a );
  gets(st);
  gets(st);

  for(int i = 0; st[i]; i++ ) {
    char c = st[i];
    if ( c >= 'a' && c <= 'z' ) {
      st[i] =  a[c-'a'];
    } else if ( c >= 'A' && c <= 'Z' ) {
      st[i] = a[c-'A'] + 'A' - 'a';
    } else if ( c == ' ' ){
    } else {
      while(1);
    }
  }
  printf("%s\n", st);

  return 0;
}



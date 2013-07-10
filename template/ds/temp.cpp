double a[1000000];  // numbers stack
char b[1000000];    // operators stack
int end = 0,k;
char s[1000000];

int level(char c) {
  switch (c) {
    case '@' : return 4;
    case '*': case '/': return 3;
    case '+': case '-': return 2;
    case '(': case ')': return 1;
  }
  return 0;
}

void cal(char c) {
  switch (c) {
    case '+' : a[k-2]+=a[k-1]; break;
    case '-' : a[k-2]-=a[k-1]; break;
    case '*' : a[k-2]*=a[k-1]; break;
    case '/' : a[k-2]/=a[k-1]; break;
    case '@' : a[k-2] = pow(a[k-2], a[k-1]);
  }
  if (a[k-2] > limit) end = 1;
  --k;
}

int main() {
  gets(s); // expression
  int id = 0,len = strlen(s),j;
  k = j = 0;
  end = 0;

  while (id < len) {
    printf("%c\n",s[id]);
    if (level(s[id]) > 0) {
      if (s[id] == '(') b[j++] = s[id];
      else if (s[id] == ')') {
        while (j >= 1 && b[j-1] != '(') cal(b[--j]);
        --j;
      }
      else {
        while (j >= 1 && ((level(s[id]) < level(b[j-1])) || (level(s[id]) == level(b[j-1]) && s[id] != '@'))) cal(b[--j]);
        b[j++] = s[id];
      }
    }
    else if (s[id] != ' ') {
      int x;
      sscanf(s+id,"%lf%n",&a[k++],&x);
      id += x-1;
    }
    id++;
    if (end) break;
  }
  while (j > 0) cal(b[--j]);
  printf("%.3f\n",a[0]);

  return 0;
}

struct node{
  int l, r, v, h;
};

int Merge(int a, int b){
  if (!a || !b) return a + b;
  if (T[a].v < T[b].v) swap(a, b);
  T[a].r = Merge(T[a].r, b);
  if (T[T[a].l].h < T[T[a].r].h) swap(T[a].l, T[a].r);
  T[a].h = T[T[a].r].h + 1;
  return a;
}

void DelMax(int &a){
  a = Merge(T[a].l, T[a].r);
}


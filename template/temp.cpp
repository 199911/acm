#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
	int A[] = {1, 2, 3, 4, 5, 6, 7};
	printf("%ld\n", lower_bound(A, A + 7, 0) - A);
	printf("%ld\n", lower_bound(A, A + 7, 100) - A);
	return 0;
}

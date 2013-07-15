int joseph(int n, int k){   // O(klogn)
	if(n<=1)return 0;
	if(k==1)return n-1;  // this line of code can be handled by caller
	int x=(n+k-1)/k;
	return (x*k+(joseph(n-x,k)*k+gm(x-n,k-1))/(k-1)+(x*k==n+k-1))%n;
}

// 0-base
int joseph(int n, int k){       // O(n)
	int a = 0;
	for (int i = 2; i <= n; i++)
		a = (a + k) % i;
	return a;
}

// 0-base , O(K + Klg(N/K)) :
LL Joseph(LL n,LL k){
	LL a = 0, i = 2;
	while (i<=n){
		if (i<n){
			LL t = (i-a-1)/k;
			if (i+t<n){
				a += t*k; i += t;
			}else{
				a += (n-1-i)*k;
				i += (n-1-i);
			}
		}
		a = (a+k)%i; ++i;
	}
	return a;
}

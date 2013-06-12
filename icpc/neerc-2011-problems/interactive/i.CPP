#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int) n; ++i)
#define pii pair <int, int>
#define fs first
#define sc second
#define mp make_pair
#define pb push_back
#define seta(a, b) memset(a, b, sizeof(a))

int n;

int get(vector<int> now){
	forn(i, now.size())
		printf("%d ", now[i]);
	puts("");
	fflush(stdout);
	int res;
	scanf("%d", &res);
	if (res == n)
		exit(0);
	return res;
}

void add(vector<int> &now){
	bool  used[50];
	memset(used, 0, sizeof used);
	forn(i, now.size()){
		used[now[i]] = 1;
	}
	int ans = -1;
	int cur = -1;
	for (int i = 1; i <= n; i++)
		if (!used[i]){
			vector<int> r = now;
			r.pb(i);
			for (int j = 1; j <= n; j ++)
				if (!used[j] && j != i)
					r.pb(j);
			int ww = get(r);
			if (ww > cur){
			 	cur = ww;
			 	ans = i;	
			}
		}
	now.pb(ans);

}

int main()
{

	cin >> n;

	vector<int> res;

	forn(i, n + 1){
		add(res);
	}

	return 0;
}
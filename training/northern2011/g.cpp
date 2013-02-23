#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++ )
#define FOE(i,a,b) for(int i = (a); i <= (b); i++ )
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

struct F {
	string name;
	int ac;
	string arg[15];
	string ret;	
} f[105];

int n;
char ts[2000];
map<string,string> mp;
vector<string> ans;

int main() {
	scanf("%d",&n);
	gets(ts);
	for (int i=0; i<n; i++) {
		gets(ts);
		//printf("%s\n",ts);
		int len = strlen(ts);
		f[i].name = "";
		f[i].ac = 0;
		char tret[15],ttyp[15];
		int ok = 0;
		for (int j=0; j<len; j++) {
			//printf("j %d\n",j);
			if (ok == 2) {
				sscanf(ts+j,"%s",tret);
				//printf("ret   %s\n",tret);
				f[i].ret = tret;
				break;	
			}
			if (ts[j] == '(') {
				ok = 1;
				continue;
			}
			if (ok) {
				sscanf(ts+j,"%s",ttyp);
				//printf("type   %s\n",ttyp);
				int tl = strlen(ttyp);
				string ta = "";
				for (int k=0; k<tl-1; k++)
					ta += ttyp[k];
				if (ta.length() > 0) f[i].arg[f[i].ac++] = ta;
				if (ttyp[tl-1] == ')') {
					j += tl+1;
					ok = 2;
				}
				else j += tl;
				continue;
			}
			f[i].name += ts[j];
		}
		/*
		cout << f[i].name << endl;
		cout << f[i].ret << endl;
		for (int j=0; j<f[i].ac; j++)
			cout << "  *" << f[i].arg[j] << endl;
		*/
	}
	
	int q;
	scanf("%d",&q);
	gets(ts);
	for (int ln=1; ln<=q; ln++) {
		gets(ts);
		int x = 0,y;
		char ttyp[15],tvar[25],rub[22];
		sscanf(ts+x,"%s%n",ttyp,&y); x += y;
		sscanf(ts+x,"%s%n",tvar,&y); x += y;
		sscanf(ts+x,"%s%n",rub,&y); x += y;
		string typ = ttyp,var = tvar;
		int len = strlen(ts);
		int ok = 0;
		string fname = "",farg[55];
		int cnt = 0;
		for (int j=x+1; j<len; j++) {
			if (ts[j] == '(') {
				ok = 1;
				continue;
			}
			if (ok) {
				sscanf(ts+j,"%s",tvar);
				int tl = strlen(tvar);
				string ta = "";
				for (int k=0; k<tl-1; k++)
					ta += tvar[k];
				if (ta.length() > 0) farg[cnt++] = ta;
				if (ttyp[tl-1] == ')') {
					j += tl+1;
					ok = 2;
				}
				else j += tl;
				continue;
			}
			fname += ts[j];
		}
		/*
		cout << fname << endl;
		for (int i=0; i<cnt; i++)
			cout << "  *" << farg[i] << endl;
		*/
		// error start :P
		
		// 1
		if (mp.find(var) != mp.end()) {
			printf("Error on line %d: Double declaration\n",ln);
			return 0;	
		}
		
		// 2
		for (int i=0; i<cnt; i++) {
			if (mp.find(farg[i]) == mp.end()) {
				printf("Error on line %d: Unknown variable\n",ln);
				return 0;
			}	
		}
		
		// 3
		int id = -1,findok = 0;
		for (int i=0; i<n; i++) {
			if (fname == f[i].name && f[i].ac == cnt) {
				int ok = 1;
				for (int j=0; j<cnt; j++)
					if (mp[farg[j]] != f[i].arg[j]) ok = 0;
				if (ok) {
					findok = 1;
					if (typ == "auto" || typ == f[i].ret) id = i;
				}
			}	
		}
		if (findok == 0) {
			printf("Error on line %d: No such function\n",ln);
			return 0;
		}
		
		// 4
		if (id == -1) {
			printf("Error on line %d: Invalid initialization\n",ln);
			return 0;
		}
		
		if (typ == "auto") {
			typ = f[id].ret;
			string tans = "";
			tans = var + " : " + typ;
			ans.push_back(tans);
		}
		mp[var] = typ;
	}
	
	for (int i=0; i<ans.size(); i++)
		cout << ans[i] << endl;
  return 0;
}

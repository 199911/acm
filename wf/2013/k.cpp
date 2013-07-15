#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define FOE(i,a,b) for(int i = (a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a,b,sizeof(a))
#define LL long long

#define N 30

#define PIS pair<int,string>


struct State {
	PIS s[3];
	State() {}
	bool operator<( const State &st ) const {
		REP( i, 3 ) if( s[i] != st.s[i] ) return s[i] < st.s[i];
		return false;
	}
};

struct Result {
	string pre, in, post;
	Result() {}
	Result( string pre, string in, string post ): pre(pre), in(in), post(post) {}
	bool operator<( const Result &res ) {
		if ( pre != res.pre ) return pre < res.pre;
		if ( in != res.in ) return in < res.in;
		return post < res.post;
	}
};

void split( string t, int mode, int left, char &root, string &lf, string &rt ) {
	int n = t.length();
	if ( mode == 0 ) {
		root = t[0];
		lf = t.substr( 1, left );
		rt = t.substr( left + 1, n - 1 - left );
	} else if ( mode == 1 ) {
		root = t[left];
		lf = t.substr( 0, left );
		rt = t.substr( left + 1, n - 1 - left ); 
	} else {
		root = t[n - 1];
		lf = t.substr( 0, left );
		rt = t.substr( left, n - 1 - left );
	}
}

map<State,bool> OK;
map<State,Result> MEMO;
int print[3][2];
string pre, in, post;
string out[3];
const string eps = string( "" );

bool recover( State st, Result &result ) {
	if ( OK.find( st ) != OK.end() ) {
		if ( OK[st] ) result = MEMO[st];
		return OK[st];
	}

/*
	cout << "recover" << endl; 
	REP( i, 3 ) {
		cout << st.s[i].second << " (" << out[st.s[i].first] << ")\n";
	}
	*/

	// detect inconsistence
	REP( i, 3 ) FOR( j, i + 1, 3 ) {
		if ( st.s[i].first == st.s[j].first ) {
			if ( st.s[i].second != st.s[j].second ) {
				OK[st] = false;
				return false;
			}
		}
	}

	int n = st.s[0].second.length();

	if ( n == 0 ) {
		OK[st] = true;
		Result res = Result( eps, eps, eps );
		MEMO[st] = res;
		result = res;
		return true;
	}
	if ( n == 1 ) {
		REP( i, n ) REP( j, n ) 
			if ( st.s[i].second != st.s[j].second ) {
				OK[st] = false;
				return false;
			}
		string str = st.s[0].second;
		Result res = Result( str, str, str );
		OK[st] = true;
		MEMO[st] = res;
		result = res;
		return true;
	}

	// size of left subtree
	Result ret = Result( eps, eps, eps ); 
	REP( left, n ) {
		char root = 0;
		State lst, rst;
		Result rlst, rrst;
		REP( i, 3 ) {
			string lf, rt;
			char rot;
			split( st.s[i].second, st.s[i].first, left, rot, lf, rt ); 
			if ( root && root != rot ) goto bye;
			root = rot;

			lst.s[i].first = print[st.s[i].first][0];
			lst.s[i].second = lf;

			rst.s[i].first = print[st.s[i].first][1];
			rst.s[i].second = rt;
		}

		if ( recover( lst, rlst ) && recover( rst, rrst ) ) {
			Result tmp;
			tmp.pre = string( "" );
			tmp.pre.append( 1, root );
			tmp.pre.append( rlst.pre );
			tmp.pre.append( rrst.pre );

			tmp.in = string( "" );
			tmp.in.append( rlst.in );
			tmp.in.append( 1, root );
			tmp.in.append( rrst.in );

			tmp.post = string( "" );
			tmp.post.append( rlst.post );
			tmp.post.append( rrst.post );
			tmp.post.append( 1, root );

			if ( ret.pre == eps || tmp < ret ) ret = tmp;
		}

bye: {}
	}

	if ( ret.pre == eps ) {
		OK[st] = false;
		return false;
	} else {
		OK[st] = true;
		MEMO[st] = ret;
		result = ret;

		return true;
	}
}


int main() {
	out[0] = string( "Pre" );
	out[1] = string( "In" );
	out[2] = string( "Post" );

	cin >> pre >> in >> post;
	int first = 1;
	for( print[0][0] = 0; print[0][0] < 3; print[0][0]++ ) 
		for( print[0][1] = 0; print[0][1] < 3; print[0][1]++ ) 
			for( print[1][0] = 0; print[1][0] < 3; print[1][0]++ ) 
				for( print[1][1] = 0; print[1][1] < 3; print[1][1]++ ) 
					for( print[2][0] = 0; print[2][0] < 3; print[2][0]++ ) 
						for( print[2][1] = 0; print[2][1] < 3; print[2][1]++ ) {
							int cnt[3]; CLR( cnt, 0 );
							REP( i, 3 ) REP( j, 2 ) cnt[print[i][j]]++;
							if ( cnt[0] == 2 && cnt[1] == 2 && cnt[2] == 2 ) {
								MEMO.clear();
								OK.clear();
								State s;
								Result res;
								s.s[0] = PIS( 0, pre );
								s.s[1] = PIS( 1, in );
								s.s[2] = PIS( 2, post );

								if ( recover( s, res ) ) {
									if ( !first ) cout << endl;
									first = 0;
									REP( i, 3 ) {
										REP( j, 2 ) {
											cout << ( ( i == 0 && j == 0 ) ? "" : " " ) << out[print[i][j]];
										}
									}
									cout << endl;
									cout << res.pre << endl;
									cout << res.in << endl;
									cout << res.post << endl;
								}
							}
						}

	return 0;
}

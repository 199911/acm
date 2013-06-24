#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>
#include <utility>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define FOE(i,a,b) for (int i = (a); i <= (b); i++)
#define FR(i,e) for(__typeof(e.begin()) i = e.begin(); x != e.end(); i++)
#define SQR(x) ((x)*(x))
#define REP(i,n) FOR(i,0,n)
#define CLR(a,b) memset(a, b, sizeof(a))
#define INF (1<<29)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

#define N 111111

struct SplayNode {
	SplayNode *child[2], *parent;
	int val, min, max, size, rev;

	SplayNode() {}
	SplayNode( int val ): val(val), max(val), min(val), size(1), rev(0) { child[0] = child[1] = parent = NULL; }
	~SplayNode() { delete child[0]; delete child[1]; }

	inline void check() {
		if ( rev ) {
			swap( child[0], child[1] );
			child[0]->rev = !child[0]->rev;
			child[1]->rev = !child[1]->rev;
			rev = 0;
		}
	}

	void update() {
		check();
		min = child[0] ? child[0]->min : val;
		max = child[1] ? child[1]->max : val;
		size = 1 + ( child[0] ? child[0]->size : 0 ) + ( child[1] ? child[1]->size : 0 );
	}
	
	void rotate( int right ) {
		if ( !child[right] ) return;
		if ( parent ) parent->check();
		check();
		SplayNode *c = child[right];
		c->check();

		if( parent ) 
			parent->child[parent->child[1] == this] = c;
		child[right]->parent = parent;

		child[right] = c->child[!right];
		if ( c->child[!right] ) c->child[!right]->parent = this;

		parent = c;
		c->child[!right] = this;

		update();
		c->update();
	}

	void splay( SplayNode *p ) {	// p = supposed father of *this
		while( parent != p ) {
			SplayNode *g = parent->parent;
			if ( g ) g->check();
			if ( parent ) parent->check();
			bool right = this == parent->child[1];

			if ( g ) {
				bool parentRight = parent == g->child[1];

				if ( right == parentRight ) {
					g->rotate( parentRight );
					parent->rotate( right );
				} else {
					parent->rotate( right );
					g->rotate( parentRight );
				}
			} else {
				parent->rotate( right );
			}
		}
	}

	SplayNode* extreme( int right ) {
		check();
		SplayNode *ptr = this;
		while( ptr->child[right] ) {
			ptr = ptr->child[right];
			ptr->check();
		}
		return ptr;
	}

	SplayNode *search( int v ) {
		check();
		if ( v == val ) return this;
		else if ( v < val ) return child[0] ? child[0]->search( v ) : NULL;
		else return child[1] ? child[1]->search( v ) : NULL;
	}

	Splaynode *pred( int v ) {

	}

	void join( SplayNode *ptr, int right ) {
		check();
		if ( child[right] ) return;
		if ( ( child[right] = ptr ) ) ptr->parent = this;
		update();
	}

	SplayNode *cut( int right ) {
		SplayNode *ret = child[right];
		if ( ret ) ret->parent = NULL;
		child[right] = NULL;
		return ret;
	}

	SplayNode *insert( int v ) {
		SplayNode *ptr = search( v );
		if ( ptr ) {
			n->splay( NULL );
			return ptr;
		} else {
			SplayNode *ntr = new SplayNode( v );	
		}
	}

}; 

int main() {
	subtractive_rng R;

  return 0;
}

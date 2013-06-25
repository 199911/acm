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
#include <bitset>
#include <map>
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
#define LINF (1LL<<60)
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

struct SplayNode {
	SplayNode *child[2], *parent;
	int key, min, max, size;
	int value, vmin, vmax;

	SplayNode(int key, int value): key(key), min(key), max(key), size(1), vmax(value), vmin(value), value(value) { child[0] = child[1] = parent = NULL; }
	~SplayNode() { delete child[0]; delete child[1]; }

	void update() {
		min = child[0] ? child[0]->min : key;
		max = child[1] ? child[1]->max : key;
		size = 1 + (child[0] ? child[0]->size : 0) + (child[1] ? child[1]->size : 0);
		vmin = std::min( std::min( (child[0] ? child[0]->vmin : INF ), ( child[1] ? child[1]->vmin : INF ) ), value );
		vmax = std::max( std::max( (child[0] ? child[0]->vmax : -INF ), ( child[1] ? child[1]->vmax : -INF ) ), value );
	}

	void rotate(bool right) {
		SplayNode *c(child[right]);
		if (parent) parent->child[parent->child[1] == this] = c;
		child[right]->parent = parent;
		parent = c;
		if (c->child[!right]) c->child[!right]->parent = this;
		child[right] = c->child[!right];
		c->child[!right] = this;
		update(); c->update(); // note the order of update!
	}

	SplayNode* splay( SplayNode *prt ) {
		while ( parent != prt ) {
			SplayNode *g(parent->parent);
			bool right(this == parent->child[1]);
			if ( g != prt ) {
				bool parentRight(parent == g->child[1]);
				if (right != parentRight) // zig-zag
					parent->rotate(right), g->rotate(parentRight);
				else                      // zig-zig
					g->rotate(parentRight), parent->rotate(right);
			} else
				parent->rotate(right);
		}
		return this;
	}

	SplayNode *extreme(bool right) {
		SplayNode *n(this);
		while (n->child[right]) n = n->child[right];
		return n;
	}

	SplayNode *search(int v) {
		SplayNode *ptr = this;
		while( ptr ) {
			if ( v < ptr->min ) return NULL;
			else if ( v < ptr->key ) ptr = ptr->child[0];
			else if ( !ptr->child[1] || v < ptr->child[1]->min ) return ptr;
			else ptr = ptr->child[1];
		}
		return ptr;
	}

	SplayNode *find( int k ) {
		SplayNode *ptr = this;
		while( ptr ) {
			if ( k < ptr->key ) ptr = ptr->child[0];
			else if ( ptr->key == k ) return ptr;
			else ptr = ptr->child[1];
		}
		return ptr;
	}

	SplayNode* pred( int k ) {
		if ( !this || k < min ) return NULL;
		else if ( k <= key ) return child[0]->pred( k );
		else if ( !child[1] || k <= child[1]->min ) return this;
		else return child[1]->pred( k );
	}

	SplayNode *succ( int k ) {
		if ( !this || k > max ) return NULL;
		else if ( k >= key ) return child[1]->succ( k );
		else if ( !child[0] || k >= child[0]->max ) return this;
		return child[0]->succ( k );
	}

	void join(SplayNode *n, bool right) {
		if (child[right]) throw;
		if ((child[right] = n)) n->parent = this;
		update();
	}

	SplayNode *cut(bool right) {
		SplayNode *n(child[right]);
		if (child[right]) child[right] = child[right]->parent = NULL; // note the order of assignment!
		update();
		return n;
	}

	SplayNode *insert(int k, int v) {
		if (this) {
			SplayNode *n(search(k));
			if (n) {
				n->splay(NULL);
				if (n->key == k)
					return n;
			}
			SplayNode *m(new SplayNode(k, v));
			m->join(n ? n->cut(true) : this, true);
			m->join(n, false);
			return m;
		}
		return new SplayNode(k, v);
	}

	void print(int ind = 0) {
		if (this) {
			child[0]->print(ind+1);
			for (int i(0); i < ind; ++ i)
				cout << "  ";
			cout << key << endl;
			child[1]->print(ind+1);
		}
	}

	void check() {
		if (child[0]) {
			if (child[0]->parent != this) throw make_pair(this, false);
			child[0]->check();
		}
		if (child[1]) {
			if (child[1]->parent != this) throw make_pair(this, true);
			child[1]->check();
		}
	}
};

int main() {
	int n, q, t;
	char str[11];
	SplayNode *T = NULL;
	
	scanf( "%d%d", &n, &q );
	T = T->insert( 0, -INF );
	T = T->insert( n + 1, -INF );
	for( int i = 1; i <= n; i++ ) {
		int tmp;
		scanf( "%d", &tmp );
		T = T->insert( i, tmp );
	}

	for( int i = 0; i < q; i++ ) {
		int a, b;
		scanf( "%s%d%d", str, &a, &b );
		if ( str[0] == 'Q' ) {
			if ( b < a ) while( 1 );
			SplayNode *ptr = T->find( a - 1 );
			if ( !ptr ) while( 1 );
			T = ptr->splay( NULL );
			ptr = T->find( b + 1 );
			if ( !ptr ) while( 1 );
			ptr->splay( T );
			ptr = T->child[1]->child[0];
			if ( !ptr ) while ( 1 );
			if ( ptr->min != a || ptr->max != b ) while( 1 );
			printf( "%d\n", ptr->vmax );
		} else {
			SplayNode *ptr = T->find( a );
			if ( !ptr ) while( 1 );
			T = ptr->splay( NULL );

			ptr->value = b;
			ptr->update();
		}
	}

	return 0;
}

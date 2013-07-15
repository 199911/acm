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
#define LL long long
#define PII pair<int,int>
#define PDI pair<double,int>
#define ISS istringstream
#define OSS ostringstream
#define gmin(a,b) { if ( b < a ) a = b; }
#define gmax(a,b) { if ( b > a ) a = b; }

struct SplayNode {
	SplayNode *child[2], *parent;

	SplayNode(): parent(NULL) { child[0] = child[1] = NULL; }

	void rotate(bool right) { // assume this != NULL, child[right] != NULL
		SplayNode *c(child[right]);
		if (parent) parent->child[parent->child[1] == this] = c;
		child[right]->parent = parent;
		parent = c;
		if (c->child[!right]) c->child[!right]->parent = this;
		child[right] = c->child[!right];
		c->child[!right] = this;
	}

	void splay() { // assume this != NULL
		while (parent) {
			SplayNode *g(parent->parent);
			bool right(this == parent->child[1]);
			if (g) {
				bool parentRight(parent == g->child[1]);
				if (right != parentRight)
					parent->rotate(right), g->rotate(parentRight);
				else
					g->rotate(parentRight), parent->rotate(right);
			} else
				parent->rotate(right);
		}
	}

	SplayNode *extreme(bool right) { // assume this != NULL
		SplayNode *n(this); n->splay();
		while (n->child[right]) n = n->child[right];
		n->splay(); return n;
	}

	void join(SplayNode *n, bool right) { // assume this != NULL
		if (child[right] || (n && n->parent)) throw;
		if ((child[right] = n)) n->parent = this;
	}

	void cut(bool right) { // assume this != NULL
		if (child[right]) child[right] = child[right]->parent = NULL; // note
	}
};

struct DynamicNode: SplayNode {
	DynamicNode *dParent;

	DynamicNode(): dParent(NULL) {}

	void weaken() {
		splay(); SplayNode *c(child[false]);
		if (c) cut(false), ((DynamicNode*)c->extreme(true))->dParent = this;
	}

	void splice() { // assume this != NULL, dParent != NULL
		dParent->weaken(); join(dParent, true); dParent = NULL;
	}

	DynamicNode* expose() { // assume this != NULL
		DynamicNode *p(this);
		while(true) {
			p = (DynamicNode*)p->extreme(true);
			if (!p->dParent) return p;
			p->splice();
		}
	}

	void dJoin(DynamicNode *n) { if (dParent) throw; dParent = n; }
	void dCut() { // assume this != NULL
		if (!dParent) splay(), cut(true);
		else dParent = NULL;
	}
};

struct Node: DynamicNode {
	int value;
}

#define N 222222

Node *node[N], *tree[N];


int main() {
	return 0;
}

#include "../utilities/template.h"

#include "../../content/data-structures/LazySegmentTree.h"

const int inf = 1e9;
static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}
int max_id() { return -inf; }
int max_op(int a, int b) {return max(a, b); }
volatile int res;

struct F{
	int time; int val;
};

F id() {
	return F{INT_MIN, 0};
};
F composition(F a, F b) {
	if (a.time >= b.time) return a;
	return b;
}
int mapping(F a, int b) {
	if (a.time != INT_MIN) return a.val;
	else return b;
}
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
	lazy_segtree<int, max_op, max_id, F, mapping, composition, id> tr(v); 
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = -inf;
		rep(k,i,j) ma = max(ma, v[k]);
		assert(ma == tr.prod(i,j));
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 30) {
			::res = tr.prod(i, j);
			int ma = -inf;
			rep(k,i,j) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else {
			tr.apply(i, j, F{it, x});
			rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}

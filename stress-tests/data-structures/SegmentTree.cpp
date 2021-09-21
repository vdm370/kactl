#include "../utilities/template.h"

static unsigned RA = 1231231;
int ra() {
	RA *= 574841;
	RA += 14;
	return RA >> 1;
}

#include "../../content/data-structures/SegmentTree.h"

// https://en.wikipedia.org/wiki/Dihedral_group_of_order_6
const int lut[6][6] = {
	{0, 1, 2, 3, 4, 5},
	{1, 0, 4, 5, 2, 3},
	{2, 5, 0, 4, 3, 1},
	{3, 4, 5, 0, 1, 2},
	{4, 3, 1, 2, 5, 0},
	{5, 2, 3, 1, 0, 4}
};

int max_id() { return INT_MIN; }
int max_op(int a, int b) {return max(a, b); }

int nonabelian_id() {return 0; }
int nonabelian_op(int a, int b) { return lut[a][b]; }

int main() {
	if (0) {
		const int N = 10000;
		vector<int>vec(N, 0);
		segtree<int, max_op, max_id> tr(vec);
		ll sum = 0;
		rep(it,0,1000000) {
			tr.set(ra() % N, ra());
			int i = ra() % N;
			int j = ra() % N;
			if (i > j) swap(i, j);
			int v = tr.prod(i, j+1);
			sum += v;
		}
		cout << sum << endl;
		// return 0;
	}

	rep(n,1,10) {
		vector<int> vec(n, 0);
		segtree<int, max_op, max_id> tr(vec);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % (n+2);

			int r = rand() % 100;
			if (r < 30) {
				int ma = max_id();
				rep(k,i,j) ma = max(ma, vec[k]);
				assert(ma == tr.prod(i,j));
			}
			else {
				i = min(i, n-1);
				tr.set(i, x);
				vec[i] = x;
			}
		}
	}

	rep(n,1,10) {
		vi vec(n);
		segtree<int, nonabelian_op, nonabelian_id> tr(vec);
		rep(it,0,1000000) {
			int i = rand() % (n+1), j = rand() % (n+1);
			int x = rand() % 6;

			int r = rand() % 100;
			if (r < 30) {
				int ma = nonabelian_id();
				rep(k,i,j) ma = lut[ma][vec[k]];
				assert(ma == tr.prod(i,j));
			}
			else {
				i = min(i, n-1);
				tr.set(i, x);
				vec[i] = x;
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}

/**
 * Author: AtCoder library + Kacper Walentynowicz
 * Date: 2021-09-08
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed segtree. Queries [,). 
 * Usage: segtree<int, op, e> seg(vec);
 * Status: stress-tested
 */
#pragma once

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
	private:
	int n, size, log;
	vector<S> d;
	void update(int k) {d[k] = op(d[2 * k], d[2 * k + 1]); }
	public:
	segtree(const vector <S>&v) : n(sz(v)) {
		log = (32 - __builtin_clz(n));
		size = 1 << log;
		d = vector<S>(2*size, e());
		rep(i, 0, n) d[size+i] = v[i];
		for (int i = size - 1; i >= 1; --i) update(i);
	}
	void set(int pos, S val) {
		pos += size; d[pos] = val;
        rep(i, 1, log + 1) update(pos >> i);
	}
	S prod(int l, int r) {
		S sml = e(), smr = e();
		for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
		}
		return op(sml, smr);
	}
};

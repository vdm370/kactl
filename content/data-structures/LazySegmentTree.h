/**
 * Author: AtCoder Library + Kacper Walentynowicz
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with good lazy propagation templates. Queries [, ). You give two monoids and one acts on the other by monoid homomorphisms.
 * Time: O(\log N).
 * Usage: Couting bitwise inversions on ranges:
struct S {mint a; int size;};
struct F {mint a, b;};
S op(S l, S r) { return S{l.a + r.a, l.size + r.size}; }
S e() { return S{0, 0}; }
S mapping(F l, S r) { return S{r.a * l.a + r.size * l.b, r.size}; }
F composition(F l, F r) { return F{r.a * l.a, r.b * l.a + l.b}; }
F id() { return F{1, 0}; } 

lazy_segtree<S, op, e, F, mapping, composition, id> seg(vec);
 * Status: tested on atcoder problems
 */
template <class S,S (*op)(S, S), S (*e)(),
          class F, S (*mapping)(F, S), F (*composition)(F, F),F (*id)()>
struct lazy_segtree {
private:
    int n, size, log;
    vector<S> d; vector<F> lz;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
    void make_pushes(int &l, int &r) {
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }
    }
public:
    lazy_segtree(const vector<S>& v) : n(int(v.size())) {
        log = 32 - __builtin_clz(n); size = 1 << log;
        d = vector<S>(2 * size, e());
        lz = vector<F>(size, id());
        rep(i, 0, n) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    void set(int p, S x) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    S prod(int l, int r) {
        if (l >= r) return e();
        make_pushes(l, r);
        S sml = e(), smr = e();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
        }
        return op(sml, smr);
    }
    void apply(int l, int r, F f) {
        if (l >= r) return;
        make_pushes(l, r);
        int initl = l, initr = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
        }
        l = initl; r = initr;
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
};

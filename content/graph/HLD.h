/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli, kpw29
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: non-exhaustive testing on library-checker website.
 */
template <bool VALS_EDGES,
class S, S (*op)(S, S), S (*e)(),
class F, S (*mapping)(F, S), F (*composition)(F, F),F (*id)()>
struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, depth, rt, pos;
	lazy_segtree <S, op, e, F, mapping, composition, id> tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		  rt(N),pos(N),tree(vector<S>(N, e())) { dfsSz(0); dfsHld(0); }
	void dfsSz(int v) {
		if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		for (int& u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B query) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			query(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		query(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void path_apply(int u, int v, F func) {
		process(u, v, [&](int l, int r) { tree.apply(l, r, func); });
	}
	S path_prod(int u, int v) {
		S res = e();
		process(u, v, [&](int l, int r) {
			res = op(res, tree.prod(l, r));
		});
		return res;
	}
	void subtree_apply(int v, F func) {
		tree.apply(pos[v] + VALS_EDGES, pos[v] + siz[v], func);
	}
	S subtree_prod(int v) {
		return tree.prod(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};

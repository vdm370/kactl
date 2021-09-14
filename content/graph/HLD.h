/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli, kpw29
 * Date: 2020-01-12
 * License: CC0
 * Description: Handles subtree and path queries simultaneously in one lazy\_segtree. Each subtree is $1$ segment, while path is $O(\log N)$ segments in the tree. $VALS\_EDGES$ being true means that values are stored in the edges, as opposed to the nodes. All values are initialized to the segtree default.
 * Time: O((\log N)^2), one logarithm for subtrees.
 * Status: non-exhaustive testing on library-checker website.
 */
template <bool VALS_EDGES,
class S, S(*op)(S, S), S(*e)(),
class F, S (*mapping)(F, S), F(*composition)(F, F), F (*id)()>
struct HLD {
	int N, tim = 0;
	vector <vi> adj;
	vi par, siz, depth, rt, pos;
	lazy_segtree<S, op, e, F, mapping, composition, id> tree;
	HLD(vector <vi> adj_, int root=0) : 
		N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), depth(N),
		rt(N,root), pos(N), tree(vector<S>(N, e())) {dfsSz(root), dfsHld(root);}
	void dfsSz(int v) {
		if (par[v] != -1) adj[v].erase(find(all(adj[v]), par[v]));
		trav(u, adj[v]){
			par[u] = v, depth[u] = depth[v] + 1;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		trav(u, adj[v]){
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template<class B> void process(int u, int v, B query) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) swap(u, v);
			query(pos[rt[v]], pos[v] + 1);
		}
		if (depth[u] > depth[v]) swap(u, v);
		query(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void path_apply(int u, int v, F func) {
		process(u, v, [&](int l, int r) {tree.apply(l, r, func); });
	}
	S path_prod(int u, int v) {
		S res = e();
		process(u, v, [&](int l, int r) {
			res = op(res, tree.prod(l, r));
		});
		return res;
	}
};

/**
 * Author: Simon Lindholm + kpw29 rework
 * Date: 2021-09-26
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, node) representing a tree.
 * No index reordering occurs.
 * The root points to itself.
 * Time: $O(|S| \log |S|)$
 * Status: Tested on BOI17 railway
 */
#pragma once

#include "LCA.h"

typedef vector<pair<int, int>> vpi;
vpi compressTree(LCA& lca, const vi& subset) {
	vi li = subset, &T = lca.time;
	auto cmp = [&](int a, int b) { return T[a] < T[b]; };
	sort(all(li), cmp);
	int m = sz(li)-1;
	rep(i,0,m) {
		int a = li[i], b = li[i+1];
		li.push_back(lca.lca(a, b));
	}
	sort(all(li), cmp);
	li.erase(unique(all(li)), li.end());
	vpi ret = {{li[0], li[0]}};
	rep(i,0,sz(li)-1) {
		int a = li[i], b = li[i+1];
		ret.emplace_back(lca.lca(a, b), b);
	}
	return ret;
}

/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set. 
 *  Left vertices are [0,n), right: [n, n+m) (!!!!)
 * Status: stress-tested
 */
#pragma once

#include "DFSMatching.h"

vi cover(vector<vi>& g, int n, int m) {
	matching solver(g);
	int res = solver.solve();
	vector<bool> lfound(n, true), seen(m);
	vi q, cover;
	rep(i,0,n) {
		if (solver.skoj[i] != -1) lfound[i] = false;
	}
	rep(i,0,n) {
		if (lfound[i]) q.push_back(i);
	}
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		assert(0 <= i && i < n);
		lfound[i] = 1;
		trav(e, g[i]) if (!seen[e-n] && solver.skoj[e] != -1) {
			seen[e-n] = true;
			q.push_back(solver.skoj[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

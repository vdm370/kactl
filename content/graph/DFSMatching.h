/**
 * Author: Kacper Walentynowicz
 * Date: 2021-09-07
 * License: CC0
 * Source:
 * Description: Simple bipartite matching algorithm. Graph $g$ should be given as normal adjacency list, no need to specify partitions explicitly
 * Time: $O(VE)$ worst case but also for $n,m \leq 10^5$ in 0.5s
 * Status: tested on SPOJ and LibraryChecker
 */
#pragma once

struct matching {
  vector<vi> v;
  int n;
  vi odw, skoj;
  matching(vector <vi> &vec) : v(vec), n(sz(vec)), odw(n, 0), skoj(n, -1) {}
  bool dfs(int x) {
      if (odw[x]) return 0;
      odw[x] = 1;
      trav(u, v[x]) {
          if (skoj[u] == -1 || dfs(skoj[u])) {
              skoj[u] = x;
              skoj[x] = u;
              return 1;
          }
      }
      return 0;
  }
  int solve() {
    int ok = 1, res = 0;
    while (ok--) {
      fill(all(odw), 0);
      rep(i, 0, n) {
          if (skoj[i] == -1 && dfs(i)) res++, ok = 1;
      }
    }
    return res;
  }
};

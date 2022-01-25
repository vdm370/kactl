/**
 * Author: Lucian Bicsi + kpw29 rework
 * Date: 2016-07-25
 * Source: https://codeforces.com/blog/entry/75885
 * Description: A dynamic data structure for rooted trees. 1-based(!!!)
 * Path queries need commutativity + neutral element.
 * Subtree queries need that + existence of inverse elements
 * Lazy propagation is possible, too.
 * Time: All operations take amortized O(\log N).
 * Status: Tested a bit on library-checker
 */
#pragma once

template<class T, T(*op)(T, T), T(*inv)(T), T(*e)()>
struct LCT {
  struct node {
    int ch[2] = {0, 0}, p = 0;
    T self = e(), path = e();        // Path aggregates
    T sub = e(), vir = e();          // Subtree aggregates
    bool flip = 0;                       // Lazy tags
  };
  vector<node> t;
  LCT(int n) : t(n + 1) {}
  void push(int x) {
    if (!x || !t[x].flip) return;
    int l = t[x].ch[0], r = t[x].ch[1];
    t[l].flip ^= 1, t[r].flip ^= 1;
    swap(t[x].ch[0], t[x].ch[1]);
    t[x].flip = 0;
  } 
  void pull(int x) {
    int l = t[x].ch[0], r = t[x].ch[1]; push(l); push(r); 
    
    t[x].path = op(op(t[l].path, t[x].self), t[r].path);
    t[x].sub = op(op(op(t[x].vir, t[l].sub), t[r].sub), t[x].self);
  }
  void set(int x, int d, int y) {
    t[x].ch[d] = y; t[y].p = x; pull(x); 
  }
  void splay(int x) { 
    auto dir = [&](int x) {
      int p = t[x].p; if (!p) return -1;
      return t[p].ch[0] == x ? 0 : t[p].ch[1] == x ? 1 : -1;
    };
    auto rotate = [&](int x) {
      int y = t[x].p, z = t[y].p, dx = dir(x), dy = dir(y);
      set(y, dx, t[x].ch[!dx]); 
      set(x, !dx, y);
      if (~dy) set(z, dy, x); 
      t[x].p = z;
    };
    for (push(x); ~dir(x); ) {
      int y = t[x].p, z = t[y].p;
      push(z); push(y); push(x);
      int dx = dir(x), dy = dir(y);
      if (~dy) rotate(dx != dy ? x : y);
      rotate(x);
    }
  }
  int access(int x) {
    int u = x, v = 0;
    for (; u; v = u, u = t[u].p) {
      splay(u); 
      int& ov = t[u].ch[1];
      t[u].vir = op(t[u].vir, t[ov].sub);
      t[u].vir = op(t[u].vir, inv(t[v].sub));
      ov = v; pull(u);
    }
    return splay(x), v;
  }
  void reroot(int x) { 
    access(x); t[x].flip ^= 1; push(x); 
  }
  void link(int u, int v) { 
    reroot(u); access(v); 
    t[v].vir = op(t[v].vir, t[u].sub);
    t[u].p = v; pull(v);
  }  
  void cut(int u, int v) {
    reroot(u); access(v);
    t[v].ch[0] = t[u].p = 0; pull(v);
  } 
  // Rooted tree LCA. Returns 0 if u and v arent connected.
  int lca(int u, int v) { 
    if (u == v) return u;
    access(u); int ret = access(v); 
    return t[u].p ? ret : 0;
  } 
  // Query subtree of u where v is outside the subtree.
  T subtree_prod(int u, int v) {
    reroot(v); access(u); return op(t[u].vir, t[u].self);
  } 
  // Query path [u..v]
  T path_prod(int u, int v) {
    reroot(u); access(v); return t[v].path;
  } 
  // Update vertex u with value v
  void set(int u, T v) {
    access(u); t[u].self = v; pull(u);
  }
  T get(int u) {
	  return t[u].self;
  }
};

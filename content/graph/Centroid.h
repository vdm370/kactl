/**
 * Author: kpw29
 * Date: 2021-08-22
 * License: CC0
 * Source: Folklore
 * Description: Centroid decomposition template.
 * Status: tested on yosupo's library-checker.
 */
#pragma once

// override calc() to do what you need
// node indexes are preserved throughout invocations
// if something is protected, it is safe to use it in calc()
struct base_centroids {
    private:
    int n; //graph size
    vector <vi> v; //0-based
    vector <bool> odw, gold;
    vi sub, maxsub;
    protected:
    vi par; //current array of nodes'parents. par[root]= -1.
    vi get_subtrees(vi &pre) { //helper fn which finds ranges [, ) of root's subtrees. 
        vi res = {};
        rep(i, 0, sz(pre)) {
            if (par[pre[i]] == pre[0]) res.push_back(i);
        }
        res.push_back(sz(pre));
        return res;
    }
    //calculate answers for the current centroid(root). Nodes given in PREORDER
    virtual void calc(int root, vi &nodes) = 0;
    private:
    void prep(int x, vi &nodes) {
        odw[x] = 1; sub[x] = 1;
        nodes.push_back(x);
        trav(u, v[x]) {
            if (!gold[u] && !odw[u]) {
                prep(u, nodes);
                sub[x] += sub[u];
                maxsub[x] = max(maxsub[x], sub[u]);
            }
        }
    }
    void cendfs(int x, int &PRE, vi &pre) {
        odw[x] = 1; pre[PRE++] = x;
        trav(u, v[x]) {
            if (!odw[u] && !gold[u]) {
                par[u] = x;
                cendfs(u, PRE, pre);
            }
        }
    }
    public:
    base_centroids(int N, vector <vi> graph) : n(N), v(graph), odw(n, false), gold(n, false), sub(n, 0), maxsub(n, 0), par(n, -1) {
    };
    void solve(int start=0) {
        vector <int> comp;
        prep(start, comp);
        int N = sz(comp), cen = -1;
        trav(node, comp) {
            maxsub[node] = max(maxsub[node], N - sub[node]);
            if (maxsub[node] <= N / 2) cen = node;
            odw[node] = 0, sub[node] = 0, maxsub[node] = 0;
        }
        int PRE = 0; 
        vi pre(N, 0);
        par[cen] = -1;
        cendfs(cen, PRE, pre);
        calc(cen, pre);
        trav(node, comp) odw[node] = 0, par[node] = -1;
        gold[cen] = 1;
        trav(u, v[cen]) {
            if (!gold[u]) solve(u);
        }
    }
};

struct centroids : base_centroids {
    centroids(int N, vector <vi> graph) : base_centroids(N, graph) {}
    void calc(int root, vi &nodes) {
        trav(node, nodes) cerr << node << "\n";
    }
};

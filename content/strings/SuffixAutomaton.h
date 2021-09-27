#include<bits/stdc++.h>
using namespace std;
/**
 * Author: kpw29 rework of cp-algorithms.com
 * Date: 2021-08-22
 * License: CC0
 * Description: Suffix automaton. Constructs a DAG efficiently maintaining
 * equivalence classes of string occurrences. LOOK AT THE PICTURE!!!
 * Each distinct string is some path through the automaton.
 * Each occurrence of string w is a path from its node to some terminal node.
 * At most 2N states and 3N edges in the whole automaton.
 * Many things done by DP, add calculations in init()
 * Time: O(n \alpha) or O(n log \alpha)
 * If you need suffix tree, use suffix links in SA for reversed string.
 * Status: tested on some string problems
 */
struct state {
    int len, link;
    map<char, int> next;
    state() : len(0), link(-1) {}
};
struct suffix_automaton {
	string input;
	vector <state> st;
	int last, size;
	vi top; vector<ll> cnt; vector<bool> odw; 
	suffix_automaton(const string &s) : input(s), last(0), size(1) {
		st.push_back(state());
		trav(c, s) add_letter(c);
		init();
	}
	void dfs(int x) {
		odw[x] = 1;
		for (auto [lett, node] : st[x].next)
			if (!odw[node]) dfs(node);
		top.push_back(x);
	}
	void init() {
		int p = last;
		cnt.resize(size, 0); odw.resize(size, 0);
		while (p > 0) cnt[p]++, p = st[p].link;
		dfs(0);
		reverse(all(top)); assert(top[0] == 0);
		for (int i = sz(top)-1; i>0; --i) {
			for (auto [lett, node] : st[top[i]].next) {
				cnt[top[i]] += cnt[node]; //dp calculations here
			}
		}
	}
	void add_letter(char c) {
		st.push_back(state());
		int cur = size++;
		st[cur].len = st[last].len + 1;
		int p = last;
		while (p != -1 && !st[p].next.count(c)) {
			st[p].next[c] = cur;
			p = st[p].link;
		}
		if (p == -1) {
			st[cur].link = 0;
		} else {
			int q = st[p].next[c];
			if (st[p].len + 1 == st[q].len) {
				st[cur].link = q;
			} else {
				st.push_back(state());
				int clone = size++;
				st[clone].len = st[p].len + 1;
				st[clone].next = st[q].next;
				st[clone].link = st[q].link;
				while (p != -1 && st[p].next[c] == q) {
					st[p].next[c] = clone;
					p = st[p].link;
				}
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
	int search(const string &s) {
		int q = 0;
		trav(c, s) {
			if (st[q].next.find(c) == st[q].next.end()) return 0;
			q = st[q].next[c];
		}
		return q;
	}
	ll count_occs(string &s) { return cnt[search(s)]; }
	string lcs(const string &T) {
		int v = 0, l = 0, best = 0, bestpos = 0;
		rep(i, 0, sz(T)) {
			while (v && !st[v].next.count(T[i])) {
				v = st[v].link;
				l = st[v].len;
			}
			if (st[v].next.count(T[i])) {
				v = st [v].next[T[i]];
				l++;
			}
			if (l > best) {
				best = l;
				bestpos = i;
			}
		}
		return T.substr(bestpos - best + 1, best);
	}
};

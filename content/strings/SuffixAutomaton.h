#include<bits/stdc++.h>
using namespace std;
/**
 * Author: tnowak
 * Date: 2021-08-22
 * License: CC0
 * Description: Suffix automaton. Constructs a DAG efficiently maintaining
 * equivalence classes of string occurrences. LOOK AT THE PICTURE! Many things done by DP on it. Examples:
 * The number of distinct substrings is the number of different paths in the automaton.
 * These can be calculated recursively by calculating for each node the number of different paths starting from that node.
 * The number of different paths starting from a node is the sum of the corresponding numbers of its direct successors,
 * plus 1 corresponding to the path that does not leave the node.
 * Each occurrence of string w is a path from its node to some terminal node
 * Time: O(n \alpha) or O(n log \alpha)
 * If you need suffix tree, use suffix links in SA for reversed string.
 * Status: tested on some string problems
 */
 struct SuffixAutomaton {
    static constexpr int sigma = 26;
    using Node = array<int, sigma>; // or map<int, int>
    Node new_node;
    vector<Node> edges;
    vector<int> link = {-1}, length = {0};
    int last = 0;
    SuffixAutomaton() {
        new_node.fill(-1);     // -1 - state nonexistent
        edges = {new_node};  // start state for empty string
    }           
    void add_letter(int c) {
        edges.emplace_back(new_node);
        length.emplace_back(length[last] + 1);
        link.emplace_back(0);
        int r = edges.size() - 1, p = last;
        while(p != -1 && edges[p][c] == -1) {
            edges[p][c] = r;
            p = link[p];
        }
        if(p != -1) {
            int q = edges[p][c];
            if(length[p] + 1 == length[q])
                link[r] = q;
            else {
                edges.emplace_back(edges[q]);
                length.emplace_back(length[p] + 1);
                link.emplace_back(link[q]);
                int q_prim = edges.size() - 1;
                link[q] = link[r] = q_prim;
                while(p != -1 && edges[p][c] == q) {
                    edges[p][c] = q_prim;
                    p = link[p];
                }
            }
        }
        last = r;
    }
    bool is_inside(vector<int> &s) {
        int q = 0;
        for(int c : s) {
            if(edges[q][c] == -1)
                return false;
            q = edges[q][c];
        }
        return true;
    }
    vector <int> get_terminals() {
        vector<int> terminals;
        int p = last;
        while(p > 0) {
          terminals.push_back(p);
          p = link[p];
        }
        return terminals;
    }
};

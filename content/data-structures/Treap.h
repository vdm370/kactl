/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct Node {
	Node *c[2] = {0, 0};
	int prio, s = 1; // by default this just counts number of children
	Node() : prio(rand()) {}
	void recalc();
};

int sum(Node* n) { return n ? n->s: 0; }
void Node::recalc() { // push lazy propagation here
	s = sum(c[0]) + 1 + sum(c[1]); 
} 

Node* attach(Node *l, Node* n, Node *r){
	n->c[0] = l, n->c[1] = r;
	n->recalc();
	return n;
}

pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	n->recalc();
	if (sum(n->c[0]) >= k) { // "n->val >= k" for lower_bound(k)
		auto [l, r] = split(n->c[0], k);
		return {l, attach(r, n, n->c[1])};
	} else { 
		auto [l, r] = split(n->c[1], k - 1 - sum(n->c[0])); // and just "k"
		return {attach(n->c[0], n, l), r};
	}
}

Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	l->recalc(); // only needed for lazy propagation
	r->recalc();
	return l->prio > r->prio ?
		attach(l->c[0], l, merge(l->c[1], r)) :
		attach(merge(l, r->c[0]), r, r->c[1]);
}

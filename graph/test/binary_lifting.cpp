#include <bits/stdc++.h>
using namespace std;

#include "../binary_lifting.cpp"

mt19937 rd(0);

void test(const vector<vector<int>> &old_adj, int root) {
	int n = old_adj.size();
	vector<int> perm(n);
	iota(perm.begin(), perm.end(), 0);
	ranges::shuffle(perm, rd);
	vector<vector<int>> adj(n);
	for (int i = 0; i < n; i++) {
		auto &a = adj[perm[i]] = old_adj[i];
		for (int &v: a) v = perm[v];
		ranges::shuffle(a, rd);
	}
	root = perm[root];

	vector<int> parent(n);
	function<void(int,int)> dfs = [&](int u, int p) {
		parent[u] = p;
		for (int v: adj[u]) if (v != p) dfs(v, u);
	};
	dfs(root, -1);

	function<bool(int, int)> is_ancestor = [&](int u, int v) {
		while (v != -1 && u != v) v = parent[v];
		return u == v;
	};
	function<int(int)> depth = [&](int v) {
		int r = 0;
		while ((v = parent[v]) != -1) r++;
		return r;
	};

	Lift lift(adj, root);
	for (int i = 0; i < n; i++) assert(lift.depth(i) == depth(i));
	uniform_int_distribution<int> distrib(0, n-1);
	for (int i = 0; i < 1000; i++) {
		int v = distrib(rd);
		int d = distrib(rd);
		int u = lift.lift(v, d);
		assert(is_ancestor(u, v));
		if (d <= depth(v)) assert(depth(u) == d);
		else assert(u == v);
	}
	for (int i = 0; i < 1000; i++) {
		int u = distrib(rd);
		int v = distrib(rd);
		int lca = lift.lca(u, v);
		assert(is_ancestor(lca, u));
		assert(is_ancestor(lca, v));
		for (int p = parent[lca]; int c: adj[lca]) {
			if (c == p) continue;
			assert(!is_ancestor(c, u) || !is_ancestor(c, v));
		}
	}
}

int main() {
	{
		// Single vertex
		vector<vector<int>> adj(1);
		test(adj, 0);
	}
	{
		// Path
		vector<vector<int>> adj(100);
		for (int i = 1; i < 100; i++) {
			adj[i-1].push_back(i);
			adj[i].push_back(i-1);
		}
		test(adj, 0);
		test(adj, 99);
		test(adj, 40);
	}
	{
		// Random
		vector<vector<int>> adj(1000);
		for (int i = 1; i < 1000; i++) {
			uniform_int_distribution<int> distrib(0, i-1);
			int p = distrib(rd);
			adj[p].push_back(i);
			adj[i].push_back(p);
		}
		test(adj, 0);
		test(adj, 300);
		test(adj, 600);
		test(adj, 900);
	}
}

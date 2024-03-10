#include "util.cpp"
#include "../../datastructures/sparseTable.cpp"
#include "../LCA_sparse.cpp"

void test(vector<vector<int>> &adj, int root) {
	int n = adj.size();

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

	LCA lca;
	lca.init(adj, root);
	for (int i = 0; i < n; i++) assert(lca.getDepth(i) == depth(i));
	for (int i = 0; i < 1000; i++) {
		int u = util::randint(n);
		int v = util::randint(n);
		int l = lca.getLCA(u, v);
		assert(is_ancestor(l, u));
		assert(is_ancestor(l, v));
		for (int p = parent[l]; int c: adj[l]) {
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
		vector<vector<int>> adj = util::path(100);
		int left = 0, mid = 40, right = 99;
		util::shuffle_graph(adj, left, mid, right);
		test(adj, left);
		test(adj, mid);
		test(adj, right);
	}
	{
		// Random
		vector<vector<int>> adj = util::random_tree(1000);
		test(adj, 0);
	}
}

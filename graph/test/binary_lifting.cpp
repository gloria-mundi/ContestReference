#include "util.cpp"
#include "../binary_lifting.cpp"

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

	Lift lift(adj, root);
	for (int i = 0; i < n; i++) assert(lift.depth(i) == depth(i));
	for (int i = 0; i < 1000; i++) {
		int v = util::randint(n);
		int d = util::randint(n);
		int u = lift.lift(v, d);
		assert(is_ancestor(u, v));
		if (d <= depth(v)) assert(depth(u) == d);
		else assert(u == v);
	}
	for (int i = 0; i < 1000; i++) {
		int u = util::randint(n);
		int v = util::randint(n);
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

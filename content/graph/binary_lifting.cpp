struct Lift {
	vector<int> dep, par, jmp;

	Lift(vector<vector<int>> &adj, int root):
			dep(adj.size()), par(adj.size()), jmp(adj.size(), root) {
		function<void(int,int,int)> dfs = [&](int u, int p, int d) {
			dep[u] = d, par[u] = p;
			jmp[u] = dep[p] + dep[jmp[jmp[p]]] == 2*dep[jmp[p]]
			       ? jmp[jmp[p]] : p;
			for (int v: adj[u]) if (v != p) dfs(v, u, d+1);
		};
		dfs(root, root, 0);
	}

	int depth(int v) { return dep[v]; }
	int lift(int v, int d) {
		while (dep[v] > d) v = dep[jmp[v]] < d ? par[v] : jmp[v];
		return v;
	}
	int lca(int u, int v) {
		v = lift(v, dep[u]), u = lift(u, dep[v]);
		while (u != v) {
			auto &a = jmp[u] == jmp[v] ? par : jmp;
			u = a[u], v = a[v];
		}
		return u;
	}
};

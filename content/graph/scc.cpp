struct SCC {
	vector<int> idx; // idx enthält Index der SCC pro Knoten
	vector<vector<int>> sccs; // Liste der Knoten pro SCC

	SCC(const vector<vector<int>> &adj): idx(ssize(adj), -1) {
		vector<int> low(ssize(adj), -1);
		vector<int> s;
		auto dfs = [&](auto &&self, int v) -> void {
			int old = low[v] = ssize(s);
			s.push_back(v);

			for (auto u : adj[v]) {
				if (low[u] < 0) self(self, u);
				if (idx[u] < 0) low[v] = min(low[v], low[u]);
			}

			if (old == low[v]) {
				sccs.emplace_back(begin(s) + old, end(s));
				for (int u: sccs.back()) idx[u] = ssize(sccs)-1;
				s.resize(old);
		}};
		for (int i = 0; i < ssize(adj); i++) {
			if (low[i] < 0) dfs(dfs, i);
	}}
};

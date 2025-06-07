constexpr int mod = 1'000'000'007, I = 10;

int max_matching(const vector<vector<int>> &adj) {
	int ans = 0;
	vector<vector<ll>> mat(ssize(adj));
	for (int _ = 0; _ < I; _++) {
		for (int v = 0; v < ssize(adj); v++) {
			mat[v].assign(ssize(adj), 0);
			for (int u : adj[v]) {
				if (u < v) {
					mat[v][u] = rand() % (mod - 1) + 1;
					mat[u][v] = mod - mat[v][u];
		}}}
		int rank = ssize(gauss(mat)); // LGS @\sourceref{math/lgsFp.cpp}@
		ans = max(ans, rank / 2);
	}
	return ans;
}

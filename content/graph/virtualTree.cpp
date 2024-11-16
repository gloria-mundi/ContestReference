// needs dfs in- and out- time and lca function
vector<int> in, out;

void virtualTree(vector<int> ind) { // indices of used nodes
	ranges::sort(ind, {}, [&](int x) { return in[x]; });
	for (int i = 1, n = ssize(ind); i < n; i++) {
		ind.push_back(lca(ind[i - 1], ind[i]));
	}
	ranges::sort(ind, {}, [&](int x) { return in[x]; });
	ind.erase(begin(ranges::unique(ind)), end(ind));

	int n = ssize(ind);
	vector<vector<int>> tree(n);
	vector<int> st = {0};
	for (int i = 1; i < n; i++) {
		while (in[ind[i]] >= out[ind[st.back()]]) st.pop_back();
		tree[st.back()].push_back(i);
		st.push_back(i);
	}
	// virtual directed tree with n nodes, original indices in ind
	// weights can be calculated, e.g. with binary lifting
}

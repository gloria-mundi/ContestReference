
namespace util {

void shuffle_adj_lists(vector<vector<int>> &adj) {
	for (auto &a: adj) ranges::shuffle(a, rd);
}

vector<vector<int>> random_tree(int n) {
	vector<vector<int>> adj(n);

	vector<vector<int>> components(n);
	for (int i = 0; i < n; i++) components[i].push_back(i);
	while (components.size() > 1) {
		int c1 = randint(components.size());
		int c2 = randint(components.size()-1);
		c2 += (c2 >= c1);

		int v1 = components[c1][randint(components[c1].size())];
		int v2 = components[c2][randint(components[c2].size())];

		adj[v1].push_back(v2);
		adj[v2].push_back(v1);

		if (components[c1].size() < components[c2].size()) swap(c1, c2);
		for (int v: components[c2]) components[c1].push_back(v);
		swap(components[c2], components.back());
		components.pop_back();
	}

	shuffle_adj_lists(adj);
	return adj;
}

vector<vector<int>> path(int n) {
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		adj[i-1].push_back(i);
		adj[i].push_back(i-1);
	}
	return adj;
}

template<typename... Ts>
void shuffle_graph(vector<vector<int>> &adj, Ts &...vertex) {
	int n = adj.size();
	vector<int> perm(n);
	iota(perm.begin(), perm.end(), 0);
	ranges::shuffle(perm, rd);

	vector<vector<int>> new_adj(n);
	for (int i = 0; i < n; i++) {
		auto &a = new_adj[perm[i]] = move(adj[i]);
		for (int &v: a) v = perm[v];
	}
	adj = move(new_adj);
	shuffle_adj_lists(adj);
	((vertex = perm[vertex]), ...);
}

}

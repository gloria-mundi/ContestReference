vector<vector<int>> adj;
vector<int> low, idx, s; // idx enthält Index der SCC pro Knoten
vector<vector<int>> sccs; // Liste der Knoten pro SCC

void visit(int v) {
	int old = low[v] = ssize(s);
	s.push_back(v);

	for (auto u : adj[v]) {
		if (low[u] < 0) visit(u);
		if (idx[u] < 0) low[v] = min(low[v], low[u]);
	}

	if (old == low[v]) {
		sccs.emplace_back(begin(s) + old, end(s));
		for (int u: sccs.back()) idx[u] = ssize(sccs)-1;
		s.resize(old);
}}

void scc() {
	low.assign(ssize(adj), -1);
	idx.assign(ssize(adj), -1);
	sccs.clear();
	for (int i = 0; i < ssize(adj); i++) {
		if (low[i] < 0) visit(i);
}}

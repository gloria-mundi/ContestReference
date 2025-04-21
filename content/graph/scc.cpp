vector<vector<int>> adj;
int sccCounter;
vector<int> low, idx, s; //idx enthält Index der SCC pro Knoten.

void visit(int v) {
	int old = low[v] = sz(s);
	s.push_back(v);

	for (auto u : adj[v]) {
		if (low[u] < 0) visit(u);
		if (idx[u] < 0) low[v] = min(low[v], low[u]);
	}

	if (old == low[v]) {
		for (int i = old; i < sz(s); i++) idx[s[i]] = sccCounter;
		sccCounter++;
		s.resize(old);
}}

void scc() {
	low.assign(sz(adj), -1);
	idx.assign(sz(adj), -1);

	sccCounter = 0;
	for (int i = 0; i < sz(adj); i++) {
		if (low[i] < 0) visit(i);
}}

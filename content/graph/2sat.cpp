constexpr int var(int i) { return i << 1; } // use this!
struct SAT2 {
	int n;
	vector<vector<int>> adj;
	vector<int> sol;
	SAT2(int vars) : n(vars*2), adj(n) {}

	void addImpl(int a, int b) {
		adj[a].push_back(b);
		adj[1^b].push_back(1^a);
	}
	void addEquiv(int a, int b) { addImpl(a, b); addImpl(b, a); }
	void addOr(int a, int b) { addImpl(1^a, b); }
	void addXor(int a, int b) { addEquiv(a, 1^b); }
	void addTrue(int a) { addImpl(1^a, a); }
	void addFalse(int a) { addTrue(1^a); }
	void addAnd(int a, int b) { addTrue(a); addTrue(b); }
	void addNand(int a, int b) { addOr(1^a, 1^b); }

	bool solve() {
		SCC scc(adj); // SCC @\sourceref{graph/scc.cpp}@
		sol.assign(n, -1);
		for (int i = 0; i < n; i++) {
			if (scc.idx[i] == scc.idx[1^i]) return false;
			sol[i] = scc.idx[i] < scc.idx[1^i];
		}
		return true;
	}
};

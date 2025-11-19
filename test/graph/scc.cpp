#include "../util.h"
#include <graph/scc.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, min<int>(100, n*(n-1) / 2 + 1)));
		Graph<NoData, true> g(n);
		g.erdosRenyi(m);

		vector<vector<int>> adj(n);
		g.forEdges([&](int a, int b){
			adj[a].push_back(b);
		});
		SCC scc(adj);

		auto reach = [&](int a) -> vector<bool> {
			vector<bool> seen(n);
			auto dfs = [&](auto &&self, int u) -> void {
				if (seen[u]) return;
				seen[u] = true;
				g.forOut(u, [&](int, int v) {
					self(self, v);
				});
			};
			dfs(dfs, a);
			return seen;
		};

		vector<int> seen(n);
		for (int i = 0; i < ssize(scc.sccs); i++) {
			for (int v: scc.sccs[i]) {
				if (scc.idx[v] != i) cerr << v << " is in scc " << i << ", but idx[" << v << "] = " << scc.idx[v] << FAIL;
				seen[v]++;
			}
		}

		for (int a = 0; a < n; a++) {
			if (seen[a] != 1) cerr << a << " occurs " << seen[a] << " times in sccs" << FAIL;
			vector<bool> reacha = reach(a);
			for (int b = 0; b < n; b++) {
				if (scc.idx[a] == scc.idx[b]) {
					if (!reacha[b]) cerr << a << " and " << b << " should be in different SCCs" << FAIL;
				} else if (scc.idx[a] < scc.idx[b]) {
					if (reacha[b]) cerr << a << " should come before " << b << " in topological order" << FAIL;
				}
			}
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500'000;
constexpr int M = 2'000'000;
void performance_test() {
	timer t;
	Graph<NoData, true> g(N);
	g.erdosRenyi(M);
	vector<vector<int>> adj(N);
	g.forEdges([&](int a, int b){
		adj[a].push_back(b);
	});

	t.start();
	SCC scc(adj);
	t.stop();
	hash_t hash = 0;
	for (int x : scc.idx) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	if (!sanitize) performance_test();
}

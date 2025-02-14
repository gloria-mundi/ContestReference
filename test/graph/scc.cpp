#include "../util.h"
#include <graph/scc.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, min<int>(100, n*(n-1) / 2 + 1)));
		Graph<NoData, true> g(n);
		g.erdosRenyi(m);

		adj.assign(n, {});
		g.forEdges([](int a, int b){
			adj[a].push_back(b);
		});
		scc();

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

		for (int a = 0; a < n; a++) {
			vector<bool> reacha = reach(a);
			for (int b = 0; b < n; b++) {
				if (idx[a] == idx[b]) {
					if (!reacha[b]) cerr << a << " and " << b << " should be in different SCCs" << FAIL;
				} else if (idx[a] < idx[b]) {
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
	adj.assign(N, {});
	g.forEdges([](int a, int b){
		adj[a].push_back(b);
	});

	t.start();
	scc();
	t.stop();
	hash_t hash = 0;
	for (int x : idx) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
